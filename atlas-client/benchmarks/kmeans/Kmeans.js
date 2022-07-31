import {ML} from 'benchmarks/atlas-ml.js';

function Kmeans_bench(size){
    var data = new Array(size);

    for(let i=0;i<size;i++){
        data[i] = new Array(3);
        for(let j=0;j<3;j++){
            data[i][j] = j;
        }
    }
    var centers = new Array(size);
    for(let i=0;i<size;i++){
        centers[i] = new Array(3);
        for(let j=0;j<3;j++){
            centers[i][j] = j;
        }
    }
    let ans = ML.KMeans(data, size, { initialization: centers });
    return ans;
}
let benchmarks = {};
benchmarks.Kmeans_bench = Kmeans_bench;
export{benchmarks};
