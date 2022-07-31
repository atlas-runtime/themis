import nlp from "benchmarks/nlp.js";
import * as std from "std";

export function Adverbs_bench(input){

	var doc = nlp(input);
	var adverbs = doc.adverbs();
	return 'Adverbs_bench done';
	
}

// Adverbs_bench(input)


