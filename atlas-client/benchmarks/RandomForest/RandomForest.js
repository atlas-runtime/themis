import {ML} from 'benchmarks/atlas-ml.js';

export function RandomForest_bench(size){

  let dataset = new Array(size);

  for(let i=0; i<size; i++){
    dataset[i] = new Array(4);

    for(let j=0; j<size; j++){
       dataset[i][j] = i+j;
    }
  }

	const trainingSet = new Array(dataset.length);
	const predictions = new Array(dataset.length);

	for (let i = 0; i < dataset.length; ++i) {
	  trainingSet[i] = dataset[i].slice(0, 3);
	  predictions[i] = dataset[i][3];
	}

	const options = {
	  seed: 3,
	  maxFeatures: 2,
	  replacement: false,
	  nEstimators: 200
	};

	const regression = new ML.RandomForestRegression(options);
	regression.train(trainingSet, predictions);
	const result = regression.predict(trainingSet);
}
// RandomForest_bench(100)
let benchmarks = {};
benchmarks.RandomForest_bench = RandomForest_bench;
export{benchmarks}
