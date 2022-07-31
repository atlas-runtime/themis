import * as std from 'std';
import * as os from 'os';
var running = true;
var w = new os.Worker("./atlas-recv.js");

w.onmessage = function (e) {
    switch (e.data.type) {
        case "start":
            w.postMessage({type: 'setup_server', 'port': 7000});
            break;
        case "count":
            print("Clients Served:", e.data.count);
            break;
    }
}
