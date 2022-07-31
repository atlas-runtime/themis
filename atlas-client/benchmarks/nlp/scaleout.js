/* benchmark specific */
import {Nouns_bench as Nouns_asd} from './benchmarks/macro/nlp/Nouns.js'
import {Verbs_bench as Verbs_asd} from './benchmarks/macro/nlp/Verbs.js'
import {Adjectives_bench as Adjectives_asd} from './benchmarks/macro/nlp/Adjectives.js'
import {Adverbs_bench as Adverbs_asd} from './benchmarks/macro/nlp/Adverbs.js'
let Nouns_bench = Nouns_asd
let Verbs_bench = Verbs_asd
let Adjectives_bench = Adjectives_asd
let Adverbs_bench = Adverbs_asd

if (local_execution == false) {
    Nouns_bench = wrapper(Nouns_bench)
    Verbs_bench = wrapper(Verbs_bench)
    Adjectives_bench = wrapper(Adjectives_bench)
    Adverbs_bench = wrapper(Adverbs_bench)
}
let input = std.loadFile('./benchmarks/macro/nlp/birds.txt');
let cc = input.length / 64
let p = ''
for (let i = 0; i < cc; i++)
    p = p + input[i]
input = p
globalThis.buffer_size = p.length
function nlp_batch_call (input) {
    Nouns_bench(input)
    Verbs_bench(input)
    Adjectives_bench(input)
    Adverbs_bench(input)
}
let w = wrapper(nlp_batch_call)
/* global inits */
demo_setup()
atlas_wrapper.start_streaming()
atlas_wrapper.warmup_system(w, [input])
atlas_wrapper.warmup_done().then(function(val) {
    scaleout_traffic(w, input)
});
