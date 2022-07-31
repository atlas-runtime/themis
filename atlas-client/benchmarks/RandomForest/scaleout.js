/* benchmark specific */
import {RandomForest_bench as RandomForest} from './benchmarks/macro/RandomForest/RandomForest.js'
let input = 100
globalThis.buffer_size = input
let RandomForest_bench = wrapper(RandomForest)
/* Core */
demo_setup()
atlas_wrapper.start_streaming()
atlas_wrapper.warmup_system(RandomForest_bench, [input])
atlas_wrapper.warmup_done().then(function(val) {
    scaleout_traffic(RandomForest_bench, input)
});
