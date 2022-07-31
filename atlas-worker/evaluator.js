globalThis.msg = parse(atlas_data)
if (msg.nonce != current_nonce) {
    print("Expected:", current_nonce, "received:", msg.nonce)
    std.exit(1)
}

if (msg.func !== "terminate") {
    t=msg.deps
    //print("System Imports:", msg.imports)
    for (let i in t) {
        // get the key --- libname
        let o = t[i]
        // we have already pushed to global state
        if (o.source === "" || o.source === undefined)  
            break;
        // execute the code as module 
        atlas.execute_script_from_buffer(o.source, o.path, 1)
    }

    function import_globals(a) {
        let str = a.imports + "\n;do_rest(" + stringify(msg) + ',' + msg.func + ');'
        atlas.execute_script_from_buffer(str, "<script>");
        return 
    }

    globalThis.do_rest = function(msg, func) {
        if (func === "terminate")
            return
        atlas_data = func.apply(this, msg.args)
        if (atlas_data === undefined)
            atlas_data = "done"
        // increase the nonce
        current_nonce++
        var results = stringify({data : atlas_data.toString(), nonce : current_nonce});
        console.write_to_client(results);
        //print(atlas_data)
        // gc every 10 pkts
        if (current_nonce % 10)
            std.gc()
    }
    import_globals(msg)
} else {
    print("Client terminated...");
}
