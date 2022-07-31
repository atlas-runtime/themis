import nlp from "benchmarks/nlp.js";
import * as std from "std";

export function Verbs_bench(input){

	var doc = nlp(input);
	var verbs = doc.verbs();
	var past_verbs = verbs.toPastTense();
	var present_verbs =  verbs.toPresentTense();
	var future_verbs =  verbs.toFutureTense();
	return 'Verbs_bench done';
	
}

// Verbs_bench(input)
