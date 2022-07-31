//  https://en.wikipedia.org/wiki/Fibonacci_number

const fibonacci = (N) => {
  if (N === 0 || N === 1) return N

  return fibonacci(N - 2) + fibonacci(N - 1)
}

export function FibonacciNumberRecursive_bench(size){
	fibonacci(size);
	return "bench_done"
}
// FibonacciNumberRecursive_bench(38)
