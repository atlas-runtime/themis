import * as std from "std";
import * as os from "os";
// the current server id we are using
let current_server = 0;
// the number of servers the thread may control
let server_count = 0;
// thread id
let tid = -1;
// nonce for avoiding replay attacks
let nonce = 0;
// the results from the async execs
let promise_results = [];
// the tasks that need to be executed on this thread
let worker_tasks = [];
// the list of all the servers bound to this thread
let server_list =  [{}];
var atlas_tools = atlas.atlas_tools;
/*
 * Craft the atlas response packet for local/remote
 */
function craft_response(send_start, worker_res, msg, mode) {
    let result = {}
    let duration = atlas_tools.get_time_diff(atlas_tools.get_time(), send_start);
    let latency = atlas_tools.get_time_diff(atlas_tools.get_time(), msg.issued_time);
    result.data = worker_res
    result.duration = duration
    result.latency = latency
    result.started = atlas_tools.get_time_diff(msg.issued_time, globalThis.gstart_time)
    result.interval = msg.inter
    result.return = atlas_tools.get_time_diff(atlas_tools.get_time(), globalThis.gstart_time)
    result.mode = mode
    result.type = "exec"
    result.tid = tid
    result.func = msg.func
    result.req_id = msg.req_id
    return result
}

/*
 * offload the request to the remote worker
 */
function send(socket, msg) {
    const str_msg = atlas.stringify(msg);
    // calculate the send time
    const send_start = atlas_tools.get_time();
    let write_res = atlas.write(socket, str_msg);
    let recv_res = receive(socket);
    // increase the nonce
    msg.nonce = msg.nonce + 1
    if (msg.nonce != recv_res.nonce) {
        print("Error, invalid nonce. Expected:", msg.nonce, "Received:", recv_res.nonce)
        std.exit(1)
    }
    let res = craft_response(send_start, recv_res.data, msg, "remote");
    res.buffer_size = write_res
    return res;
}

/*
 * Receive the response from the atlas worker
 */
function receive(sock) {
    // Receive data
    let data = atlas.read(sock);
    // parse the results
    const parse_res = atlas.parse(data);
    return parse_res;
}

function pick_server() {
    let tmp = current_server % server_count
    current_server++
    let srv = server_list[tmp]
    return srv
}

async function do_task(sock, msg) {
    return send(sock, msg, nonce)
}

var parent = os.Worker.parent;

/*
 * Worker request handler. Communicates with the parent thread and 
 * sends/receives offloading messages from/to the parent thread and the workers
 */
function handle_msg(e) {
    var ev = e.data;
    switch(ev.type) {
        case "tid" :
            tid = ev.tid;
            globalThis.gstart_time = ev.gstart_time
            break;
        case "server" :
            server_list[current_server] = ev.msg
            current_server++
            // update the number of servers
            server_count = server_list.length
            break;
        case "task" :
            worker_tasks.push(ev.msg)
            break;
        case "task_streaming":
            // get a server
            let srv = pick_server()
            let msg = ev.msg
            msg.nonce = srv['nonce']
            msg['nodeIp'] = srv['ip']
            // push the task and store in the promises array
            let val = do_task(srv['socket'], msg)
            val.then(function(result) { 
                //val.then(function(result) {
                srv['nonce'] = msg.nonce
                srv['nodeId'] = srv['id']
                parent.postMessage({type: "streaming_done", "values" : result})
            });
            break;
        case "ready":
            parent.postMessage({type : "start_reading"})
            break;
    }
}
parent.onmessage = handle_msg;
