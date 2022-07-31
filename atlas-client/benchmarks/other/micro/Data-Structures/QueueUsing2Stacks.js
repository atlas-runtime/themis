// implementation of Queue using 2 stacks
// contribution made by hamza chabchoub for a university project

class Queue1 {
  constructor () {
    this.inputStack = []
    this.outputStack = []
  }

  // Push item into the inputstack
  enqueue (item) {
    this.inputStack.push(item)
  }

  dequeue (item) {
    // push all items to outputstack
    this.outputStack = []
    if (this.inputStack.length > 0) {
      while (this.inputStack.length > 0) {
        this.outputStack.push(this.inputStack.pop())
      }
    }
    // display the top element of the outputstack
    if (this.outputStack.length > 0) {
      // console.log(this.outputStack.pop())
      // repush all the items to the inputstack
      this.inputStack = []
      while (this.outputStack.length > 0) {
        this.inputStack.push(this.outputStack.pop())
      }
    }
  }

  // display elements of the inputstack
  listIn () {
    let i = 0
    while (i < this.inputStack.length) {
      //console.log(this.inputStack[i])
      i++
    }
  }

  // display element of the outputstack
  listOut () {
    let i = 0
    while (i < this.outputStack.length) {
      //console.log(this.outputStack[i])
      i++
    }
  }
}


export function QueueUsing2Stacks_bench(size){

  const myQueue = new Queue1()

  for (var i=0; i< size; i++){
    myQueue.enqueue(i)
  }
  for (var i=0; i< size; i++){
    myQueue.dequeue(i)
  }
  return "bench_done"
}
// QueueUsing2Stacks_bench(4000)
