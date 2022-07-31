#! /bin/bash
# time: print real in seconds, to simplify parsing
TIMEFORMAT="%3R" # %3U %3S"
cd ../
ATLAS_HOME=../
LB_DIR=${ATLAS_HOME}/atlas-client
SGX_DIR=${ATLAS_HOME}/atlas-worker
QJS_DIR=${ATLAS_HOME}/atlas-qjs/src
RUN_CMD="stdbuf -oL ${QJS_DIR}/qjs atlas.js " 

bench() {
    IN=benchmarks/macro/$1
    OUT=benchmarks/rpi/$1/results
    mkdir -p ${OUT}
    echo executing $1 using $2 workers $3, $(date) | tee -a ${OUT}/../run.res
    EXEC="${RUN_CMD} --file ${IN}/streaming.js --threads $2 --servers $2 --warmup_rounds 1 $4" 
    echo ${EXEC} > run.sh
    echo $1: $({ bash run.sh > ${OUT}/run_$2$3;  } 2>&1; tail -n 1 ${OUT}/run_$2$3;  sort -g -k 1,1  ${OUT}/run_$2$3 > r1; mv r1 ${OUT}/run_$2$3; rm -f r1;) | tee -a ${OUT}/../run.res

    #rm -f run.sh
}

do_bench() {
    # reset the file 
    rm -f benchmarks/rpi/$1/run.res
    mkdir -p benchmarks/rpi/$1
    touch benchmarks/rpi/$1/run.res
    # local execution, the number of server/threads does not really matter, they go unused
    bench $1 0 "local" "--local"
    # start executing every benchmark
    #for i in 1 2 4
    #do
    #    bench $1 $i ''
    #done
    ## remote execution using dynamic scheduling
    #bench $1 4 "scaling" "--scaling"

}

#do_bench crypto_benchmark
do_bench crypto
do_bench ed
do_bench nlp
do_bench kmeans
do_bench signal
do_bench simple-pw
do_bench gnome
do_bench dectree
do_bench dj
