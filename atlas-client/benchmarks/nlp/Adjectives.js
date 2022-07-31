import nlp from "benchmarks/nlp.js";
import * as std from "std";

export function Adjectives_bench(input){

	var doc = nlp(input);
	var adjectives = doc.adjectives();
	return 'Adjectives_bench done';

}

// Adjectives_bench(input)


