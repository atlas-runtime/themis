//// Setup server related code
//var w = new os.Worker("./atlas-recv.js");
//w.onmessage = function (e) {
//    switch (e.data.type) {
//        case "start":
//            w.postMessage({type: 'setup_server', 'port': 7001});
//            break;
//        case "count":
//            print("Clients Served:", e.data.count);
//            break;
//    }
//}
// Setup client related code
// parse the user arguments
const opts = atlas.atlas_tools.parse_args(scriptArgs)
// evaluate the arguments
atlas.atlas_tools.evaluate_args(opts)
atlas.atlas_wrapper.bootstrap()
atlas.atlas_battery.start();
// main execution
if (atlas.local_execution == false) {
    // remote offloading
    atlas.atlas_wrapper.spawn_workers();
} else {
    //execute locally
    atlas.atlas_wrapper.execute_script();
}
