import {ML} from 'benchmarks/atlas-ml.js';

export function LinearRegression_bench(size){
	let x = new Array(size);
	let y = new Array(size);
	for(let i=0; i<size; i++){
		y[i] = i;
	}
	let j=0;
	for(let i=0; i<size/2; i=i+0.5){

		x[j] =i;
		j++
	}

	let regression = new ML.SimpleLinearRegression(x, y);
	regression.slope// 2
	regression.intercept // -1
	regression.coefficients// [-1, 2]
	regression.predict(3); // 5
	regression.computeX(3.5); // 2.25

	(regression.score(x, y));
}
// LinearRegression_bench(5000000)
let benchmarks = {};
benchmarks.LinearRegression_bench = LinearRegression_bench;
export{benchmarks};
