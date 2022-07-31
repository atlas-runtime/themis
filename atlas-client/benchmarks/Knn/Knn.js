import {ML} from 'benchmarks/atlas-ml.js';

function Knn_bench(size){
    return 0;
    var train_dataset = new Array(size);
    for(let i=0;i<size;i++){
        train_dataset[i] = new Array(3);
        for(let j=0;j<3;j++){
            train_dataset[i][j] = j+i;
        }
    }
    var train_labels = new Array(size);
    for(let i=0;i<size;i++){
        train_labels[i] = i%2;
    }
    var knn = new ML.KNN(train_dataset, train_labels, {k:2})
    var test_dataset = new Array(size);
    for(let i=0;i<size;i++){
        test_dataset[i] = new Array(3);
        for(let j=0;j<3;j++){
            test_dataset[i][j] = j;
        }
    }
    var ans = knn.predict(test_dataset)
}

let benchmarks = {};
benchmarks.Knn_bench = Knn_bench;
export{benchmarks};
