import * as std from "std";
import * as os from "os";
var clients_served = 0;
// since the server worker doesn't have to understand neither the wrapper or the other
// hacks the client worker has to do, we just replace the wrapper wrapper to return
// the same function
//globalThis.wrapper = function(a) { return a;};
function import_globals(msg, fd) {
    let str = msg.imports + "\n;do_rest(" + atlas.stringify(msg) + ',' + fd + ',' + msg.func + ');'
    //print('Executing\n', atlas.stringify(msg), '\n');
    atlas.execute_script_from_buffer(str, "<script>", 1);
}

globalThis.do_rest = function(msg, fd, func) {
    atlas_data = func.apply(this, msg.args)
    if (atlas_data === undefined)
        atlas_data = "done"
    // increase the nonce
    current_nonce++
    var results = atlas.stringify({data : atlas_data.toString(), nonce : current_nonce});
    atlas.write(fd, results);
    // garbage collect
    if (current_nonce % 10)
        std.gc()
}

function handshake(p) {
    // receive public key of the client
    atlas.recv_pubkey(p);
    // send our public key
    atlas.send_pubkey(p);
    // generate and send the encryption key
    atlas.gen_and_send_enc_key(p);
    globalThis.current_nonce = 0;
}

function handle_user_data(p) {
    var client_data = ''
    while (true) {
        client_data = atlas.read(p);
        if (client_data === '')
            break;
        atlas.execute_script_from_buffer("globalThis.atlas_data =" + client_data, "<input>", 0);
        // if we received a terminating signal, close the sockets!
        if (atlas_data.func === "terminate")
            break;
        let msg = atlas.parse(atlas_data);
        let t = msg.deps;
        for (let i in t) {
            // get the key --- libname
            let o = t[i]
            // we have already pushed to global state
            if (o.source === "" || o.source === undefined)  
                break;
            atlas.execute_script_from_buffer(o.source, o.path, 1)
        }
        import_globals(msg, p)
    }
}

function setup_server(port) {
    while (1) {
        // open a new socket to accept connections
        let s = atlas.socket();
        // bind to the local address
        var p = atlas.server_setup(s, "127.0.0.1", port);
        // key handshake
        handshake(p);
        // start reading data
        handle_user_data(p);
        // close the accept socket
        atlas.close(p);
        // close the server socket
        parent.postMessage({type: 'count', count: ++clients_served});
        atlas.close(s);
    }
}

/*
 * Worker request handler. Communicates with the parent thread and 
 * sends/receives offloading messages from/to the parent thread and the workers
 */

var parent = os.Worker.parent;

function handle_msg(e) {
    var ev = e.data;
    switch(ev.type) {
        case "setup_server" :
            print('Setting up server', e.data.port);
            setup_server(e.data.port);
            break;
    }
}
parent.onmessage = handle_msg;
parent.postMessage({ type: "start"}); 
