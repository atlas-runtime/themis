var TrieNode = function TrieNode (key, parent) {
  this.key = key
  this.count = 0
  this.children = Object.create(null)
  if (parent === undefined) {
    this.parent = null
  } else {
    this.parent = parent
  }
}

function Trie () {
  // create only root with null key and parent
  this.root = new TrieNode(null, null)
}

// Recursively finds the occurence of all words in a given node
Trie.findAllWords = function (root, word, output) {
  if (root === null) return
  if (root.count > 0) {
    if (typeof output === 'object') { output.push({ word: word, count: root.count }) }
  }
  var key
  for (key in root.children) {
    word += key
    this.findAllWords(root.children[key], word, output)
    word = word.slice(0, -1)
  }
}

Trie.prototype.insert = function (word) {
  if (typeof word !== 'string') return
  if (word === '') {
    this.root.count += 1
    return
  }
  var node = this.root
  var len = word.length
  var i
  for (i = 0; i < len; i++) {
    if (node.children[word.charAt(i)] === undefined) { node.children[word.charAt(i)] = new TrieNode(word.charAt(i), node) }
    node = node.children[word.charAt(i)]
  }
  node.count += 1
}

Trie.prototype.findPrefix = function (word) {
  if (typeof word !== 'string') return null
  var node = this.root
  var len = word.length
  var i
  // After end of this loop node will be at desired prefix
  for (i = 0; i < len; i++) {
    if (node.children[word.charAt(i)] === undefined) return null // No such prefix exists
    node = node.children[word.charAt(i)]
  }
  return node
}

Trie.prototype.remove = function (word, count) {
  if (typeof word !== 'string') return
  if (typeof count !== 'number') count = 1
  else if (count <= 0) return

  // for empty string just delete count of root
  if (word === '') {
    if (this.root.count >= count) this.root.count -= count
    else this.root.count = 0
    return
  }

  var child = this.root
  var len = word.length
  var i, key
  // child: node which is to be deleted
  for (i = 0; i < len; i++) {
    key = word.charAt(i)
    if (child.children[key] === undefined) return
    child = child.children[key]
  }

  // Delete no of occurences specified
  if (child.count >= count) child.count -= count
  else child.count = 0

  // If some occurences are left we dont delete it or else
  // if the object forms some other objects prefix we dont delete it
  // For checking an empty object
  // https://stackoverflow.com/questions/679915/how-do-i-test-for-an-empty-javascript-object
  if (child.count <= 0 && (Object.keys(child.children).length && child.children.constructor === Object)) {
    child.parent.children[child.key] = undefined
  }
}

Trie.prototype.findAllWords = function (prefix) {
  var output = []
  // find the node with provided prefix
  var node = this.findPrefix(prefix)
  // No such prefix exists
  if (node === null) return output
  Trie.findAllWords(node, prefix, output)
  return output
}

Trie.prototype.contains = function (word) {
  // find the node with given prefix
  var node = this.findPrefix(word)
  // No such word exists
  if (node === null || node.count === 0) return false
  return true
}

Trie.prototype.findOccurences = function (word) {
  // find the node with given prefix
  var node = this.findPrefix(word)
  // No such word exists
  if (node === null) return 0
  return node.count
};

// To test
export function Trie_bench (size) {
  var x = new Trie()
  for(var i =0; i < size ; i++){
    x.insert(i.toString())
  }

   for(var i =0; i < size; i++){
    x.remove(i.toString())
  }
  return "bench_done"
}
// Trie_bench(300000)
