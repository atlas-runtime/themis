/* benchmark specific */
import {Knn_bench as Knn} from './benchmarks/macro/Knn/Knn.js'
let input = 1500
globalThis.buffer_size = input
let Knn_bench = wrapper(Knn)
/* Core */
demo_setup()
atlas_wrapper.start_streaming()
atlas_wrapper.warmup_system(Knn_bench, [input])
atlas_wrapper.warmup_done().then(function(val) {
    scaleout_traffic(Knn_bench, input)
});
