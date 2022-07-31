import {math} from 'benchmarks/math/math.js';
let a = math.add(12,34);
let s = math.sub(1,6);
let d = math.div(1,0);
let m = math.mult(1,5);
// gather all the promises and resolve the results
Promise.allSettled([a, s, d, m])
    .then(function(results) {
        // print the results for each request
        results.forEach((result) => console.log(result.value));
        // complete execution and exit the program
        print("Execution completed, exiting...");
        atlas.terminate();
        return ;
    });
