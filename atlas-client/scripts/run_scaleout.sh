#! /bin/bash
# time: print real in seconds, to simplify parsing
TIMEFORMAT="%3R" # %3U %3S"
cd ..
if [ -z "${ATLAS_HOME}" ]; then
    echo "Please set ATLAS_HOME variable the root of atlas"
    exit 1
fi
if [ -z "${SGX_SDK}" ]; then
    echo "Please set SGX_SDK variable to the root of SGX: eg export SGX_SDK=/opt/intel/sgxsdk/"
    echo "Source SGX_SDK/environment"
    exit 1
fi
LB_DIR=${ATLAS_HOME}/lb
SGX_DIR=${ATLAS_HOME}/sgx_js
QJS_DIR=${ATLAS_HOME}/quickjs
RUN_CMD="stdbuf -oL ${QJS_DIR}/qjs_c daemon.js " 
reset_sgx() {
    cd ${SGX_DIR}; 
    pkill -9 app; bash ser.sh $1 > /dev/null
    cd ${LB_DIR}
    sleep 4
}

bench() {
    reset_sgx $2
    IN=macro/$1
    OUT=macro/$1/results
    echo executing $1 using $2 workers $3, $(date) | tee -a ${IN}/run_scaleout.res
    mkdir -p ${OUT}
    EXEC="${RUN_CMD} --file ${IN}/scaleout.js --threads $2 --servers $2 --warmup_rounds 1" 
    echo ${EXEC} > run.sh
    echo $1: $({ bash run.sh > ${OUT}/run_sc$2$3;  } 2>&1; tail -n 1 ${OUT}/run_sc$2$3;  sort -g -k 1,1  ${OUT}/run_sc$2$3 > r1; mv r1 ${OUT}/run_sc$2$3; rm -f r1;) | tee -a ${IN}/run_scaleout.res

    #rm -f run.sh
}

do_scaleout() {
    # reset the file 
    rm -f macro/$1/run_scaleout.res
    touch macro/$1/run_scaleout.res
    # start executing every benchmark
    for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
    do
        bench $1 $i $2
        echo "Sleepin"
        sleep 1
    done
}




#do_scaleout crypto
#do_scaleout nlp
#do_scaleout kmeans
#do_scaleout gnome
#do_scaleout dectree
#do_scaleout dj
#do_scaleout ed
#do_scaleout signal
do_scaleout simple-pw
