## Themis: A Secure Decentralized Framework

> _Themis is a Secure Decentralized Framework for Microservice Interaction in Serverless Computing_

## Themis at a Glance

Themis is a framework for secure service-to-service interaction targeting modern microservice environments and their underlying service mesh architectures.
Themis builds on a notion of decentralized identity management to allow confidential and authenticated service-to-service interaction without the need for a centralized certificate authority.
The current Themis prototype is embedded in Atlas, a runtime environment for automated offloading and scale-out of JavaScript programs.

More details are provided in our [paper](https://doi.org/10.1145/3538969.3538983), presented at [ARES22](https://www.ares-conference.eu/).


## Citing Themis

To cite Themis, use the following bibtex entry:

```bibtex
@article{themis:ares:2022,
  title={Themis: a secure decentralized framework for microservice interaction in serverless computing},
  author={Aktypi, Angeliki and Karnikis, Dimitris and Vasilakis, Nikos and Rasmussen, Kasper},
  year = {2022},
  isbn = {978-1-4503-9670-7/22/08},
  publisher = {Association for Computing Machinery},
  address = {New York, NY, USA},
  url = {https://doi.org/10.1145/3538969.3538983},
  doi = {10.1145/3538969.3538983},
  booktitle = {The 17th International Conference on Availability, Reliability and Security},
  articleno = {1},
  numpages = {11},
  keywords = {DHT; Security; Serverless; Service mesh},
  location = {Vienna, Austria},
  series = {ARES 2022}
}
```

## Building and Running Themis Benchmarks

The current Themis prototype is embedded in Atlas, a runtime environment for automated offloading and scale-out of JavaScript programs.
Atlas is built on top of QuickJS, and packaged as a "peer" node---which can act as both sender and receiver of requests.
The documentation below calls sending nodes _clients_ and receiver nodes _servers_ (mostly for running the experiments).

The main steps for running our prototype are as follows: (1) Build the QuickJS peer interpreter; (2) Launch one or more nodes; (3) Fire up a benchmark.

For the first step, building a peer interpreter, run 

```sh
cd atlas-qjs/src
make 
```

This will produce the qjs binary that can be used both for offloading tasks from the client, but also act as a server.
To disable Themis's end-to-end encryption---say, to measure performance differences between the two implementations---simply append `NO_ENCRYPTION=1` to `make`.

For the second step, building a server interpreter, run:

```sh
cd atlas-client
../atlas-qjs/src/qjs server_only.js
```

This will launch a peer to accept requests at port 7000.

For the third step, launching one of the benchmarks, run:

```sh
$ cd atlas-client
$ ../atlas-qjs/src/qjs atlas.js --file benchmarks/crypto_benchmark/run.js --log crypto.log --servers 1
```

This particular command runs an encrypt-and-sign service benchmark called `crypto_benchmark`.
Load generation can be found at each benchmark's [run](./atlas-client/benchmarks/crypto_benchmark/run.js) module.
Upon completion of the benchmark, the execution log---with latencies, duration, and other metadata---is written to a `<b>.log` file, where `<b>` is the name of the benchmark.

Here is an example log file---columns show start time, duration, latency, number of bytes, request interval, end time, bandwidth (mbit/sec), mode (local, remote, etc), thread ID, and some additional metadata.

```
0.025   0.088      0.092    88244   800       0.117   7.318     remote  0          exec  benchmarks.encrypt_sign  0           
0.827   0.087      0.089    10248   800       0.916   0.878     remote  0          exec  benchmarks.encrypt_sign  1           
1.628   0.069      0.072    10248   800       1.7     1.086     remote  0          exec  benchmarks.encrypt_sign  2           
2.43    0.072      0.075    10248   800       2.505   1.042     remote  0          exec  benchmarks.encrypt_sign  3           
3.232   0.07       0.072    10248   800       3.304   1.086     remote  0          exec  benchmarks.encrypt_sign  4           
4.033   0.073      0.076    10248   800       4.109   1.029     remote  0          exec  benchmarks.encrypt_sign  5           
4.834   0.036      0.037    10248   800       4.871   2.113     remote  0          exec  benchmarks.encrypt_sign  6           
5.636   0.084      0.086    10248   800       5.722   0.909     remote  0          exec  benchmarks.encrypt_sign  7           
6.438   0.034      0.037    10248   800       6.475   2.113     remote  0          exec  benchmarks.encrypt_sign  8           
7.24    0.112      0.115    10248   800       7.355   0.680     remote  0          exec  benchmarks.encrypt_sign  9           
8.042   0.076      0.079    10250   800       8.121   0.990     remote  0          exec  benchmarks.encrypt_sign  10          
8.844   0.069      0.072    10250   700       8.916   1.086     remote  0          exec  benchmarks.encrypt_sign  11          
9.545   0.071      0.075    10250   700       9.62    1.043     remote  0          exec  benchmarks.encrypt_sign  12          
10.248  0.045      0.046    10250   700       10.294  1.700     remote  0          exec  benchmarks.encrypt_sign  13          
10.948  0.059      0.062    10250   700       11.01   1.261     remote  0          exec  benchmarks.encrypt_sign  14          
11.65   0.067      0.07     10250   700       11.72   1.117     remote  0          exec  benchmarks.encrypt_sign  15          
12.352  0.046      0.049    10250   700       12.401  1.596     remote  0          exec  benchmarks.encrypt_sign  16          
13.054  0.068      0.07     10250   700       13.124  1.117     remote  0          exec  benchmarks.encrypt_sign  17          
13.755  0.062      0.065    10250   700       13.82   1.203     remote  0          exec  benchmarks.encrypt_sign  18          
...
```

