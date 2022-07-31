import {ML} from 'benchmarks/atlas-ml.js';


//2000
export function NaiveBayes_bench(size){

  let caseq = new Array(size);

  for(let i=0; i<caseq.length; i++){
    caseq[i] = new Array(size);

    for(let j=0; j<size; j++){
       caseq[i][j] = j+i
    }
  }
  let predictions = new Array(size)
  for(let i=0; i<size; i++){
     predictions[i] = i%2; 
  }
  // print(predictions)
	var model = new ML.NaiveBayes.GaussianNB();
	model.train(caseq, predictions);
	predictions = model.predict(caseq);
	// print(predictions)
}
let benchmarks = {}
benchmarks.NaiveBayes_bench = NaiveBayes_bench;
export{benchmarks}
// NaiveBayes_bench(2000)
