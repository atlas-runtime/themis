import * as std from 'std';
import * as os from 'os';

async function setup_offloading_client() {

}

function import_globals(msg, port) {
    let str = msg.imports + "\n;do_rest(" + atlas.stringify(msg) + ',' + port + ',' + msg.func + ');'
    atlas.execute_script_from_buffer(str, "<script>", 1);
}

globalThis.do_rest = function(msg, port, func) {
    atlas_data = func.apply(this, msg.args)
    if (atlas_data === undefined)
        atlas_data = "done"
    // increase the nonce
    current_nonce++
    var results = atlas.stringify({data : atlas_data.toString(), nonce : current_nonce});
    atlas.write(port, results);
    // garbage collect
    if (current_nonce % 10)
        std.gc()
}

// allocate 20 clients
atlas.allocate_clients();
// open a new socket to accept connections
let s = atlas.socket()
// perma loop that accepts connections :)
while (1) {
    var current_nonce = 0;
    // setup bind, listen, accept
    let p = atlas.setup_server(s, "127.0.0.1", 7000);
    // receive public key of the client
    let pubkey = atlas.recv_pubkey(p);
    // send our public key
    atlas.send_pubkey(p);
    atlas.gen_and_send_enc_key(p);

    while (true) {
        var ad = atlas.read(p);
        if (ad === "")
            break;
        atlas.execute_script_from_buffer("var atlas_data =" + ad, "<input>", 0);
        //print(atlas.stringify(atlas_data));
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
    print("Exiting");
    // cleanup 
    atlas.close(p);
    //atlas.close(s);
}
