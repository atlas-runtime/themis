import {Nouns_bench} from 'benchmarks/nlp/Nouns.js'
let input = std.loadFile('./benchmarks/nlp/birds.txt');
input = ''
let cc = input / 64
for (let i = 0; i < cc; i++)
    input[i] = cc[i]
/*
 * Functionality for generating and scheduling packets on different atlas.intervals
 */
let promise_results = []
let step = 0
let last_step = 0;
function generate_traffic(func, ...args) {
    // calculate how many function we have received
    var received_func_count = atlas.atlas_get_received_function_count(func);
    let time_out = os.setTimeout(function() {
        // print only when the atlas.interval switches, no reason to spam the stdio
        if (last_step !== step) {
            print("Pkt Received:", received_func_count);
            last_step = step;
        }
        if (atlas.local_execution === true)
            atlas.pkt_sent++;
        // resolve the promise
        promise_results.push(func(...args))
        generate_traffic(func, ...args);
    }, atlas.interval);

    // have we received 120 packets?
    if (received_func_count >= 120) {
        print("Resolving " + received_func_count + " packets...");
        os.clearTimeout(time_out);
        // gather all the results and print them
        Promise.allSettled(promise_results)
            .then(function(results) {
                // you might want to print this, but the output IS HUGE
                // var i = 0;
                // print the results for each request
                // results.forEach((result) => print('Pkt ID:', i++, "Result:", result.value));
                // complete execution and exit the program
                print("Execution completed, exiting...");
                // force connection stop
                atlas.terminate();
                return ;
            });
    }
    // interval switch algorithm
    if (atlas.pkt_sent < 10 && step == 0) {
        step = 1
        atlas.interval = 800;
    } else if (atlas.pkt_sent > 10 && atlas.pkt_sent < 25 && step == 1) {
        atlas.interval = 700;
        step = 2
    } else if (atlas.pkt_sent > 25 && atlas.pkt_sent < 55 && step == 2) {
        atlas.interval = 400;
        step = 3;
    } else if (atlas.pkt_sent > 55 && atlas.pkt_sent < 80 && step == 3) {
        atlas.interval = 200;
        step = 4
    } else if (atlas.pkt_sent > 80 && atlas.pkt_sent < 100 && step == 4) {
        atlas.interval = 500;
        step = 5
    } else if (atlas.pkt_sent > 100 && atlas.pkt_sent < 120 && step == 5) {
        atlas.interval = 900;
        step = 6
    }
}

// start generating traffic
generate_traffic(Nouns_bench, input);
