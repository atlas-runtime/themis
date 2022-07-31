/* benchmark specific */
import {NaiveBayes_bench as NaiveBayes} from './benchmarks/macro/NaiveBayes/NaiveBayes.js'
let input = 2000
globalThis.buffer_size = input
let NaiveBayes_bench = wrapper(NaiveBayes)
/* Core */
demo_setup()
atlas_wrapper.start_streaming()
atlas_wrapper.warmup_system(NaiveBayes_bench, [input])
atlas_wrapper.warmup_done().then(function(val) {
    scaleout_traffic(NaiveBayes_bench, input)
});
