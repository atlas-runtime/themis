import nlp from "benchmarks/nlp.js";
export function Nouns_bench(input){
	var doc = nlp(input);
	var nouns = doc.nouns();
	let plural_nouns = nouns.toPlural();
	let singular_nouns = nouns.toSingular();
	return singular_nouns;
}
