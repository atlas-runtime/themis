import {ML} from 'benchmarks/atlas-ml.js';
function DecisionTree_bench(size){
	let  x = new Array(size);
	let  y = new Array(size);
	let val = 0.0;
	for (let i = 0; i < x.length; ++i) {
	  x[i] = val;
	  y[i] = Math.sin(x[i]);
	  val += 0.01;
	}
	const reg = new ML.DecisionTreeRegression();

	reg.train(x, y);
	const estimations = reg.predict(x);
}
let benchmarks = {};
benchmarks.DecisionTree_bench = DecisionTree_bench;
export{benchmarks};
