export {}
class TrieNode {
  char: string
  count: number = 0
  countPrefix: number = 0
  children: { [key: string]: TrieNode | undefined } = {}
  constructor (char: string) {
    this.char = char
  }
};
class Trie {
  trie: TrieNode
  /**
   * @description Initialize the trie
   */
  constructor () {
    this.trie = new TrieNode('/')
  }

  /**
   * @description Insert strings into the trie
   * @param str the string to be inserted
   * @param count number of `str` to be inserted, can be negative for deleting x from the trie
   */
  insert (str: string, count: number = 1): void {
    let cur = this.trie
    for (const char of str) {
      cur.children[char] ??= new TrieNode(char)
      cur = cur.children[char]!
      cur.countPrefix += count
    }
    cur.count += count
  }

  /**
   * Traverse the trie with a callback function
   * @param str An input string
   * @param callbackfn A callback function. traverse calls the callbackfn function one time for each char in `str`, however it may skip ending chars in str if the trie has no children to go deeper, the returned char from callbackfn will be used as the direction of traversing
   * @param thisArg An object to which the this keyword can refer in the callbackfn function. If thisArg is omitted, undefined is used as the this value
   */
  traverse (str: string, callbackfn: (char: string, idx: number, node: TrieNode) => string, thisArg?: any): void {
    let cur = this.trie
    for (let i = 0; i < str.length; i++) {
      const retChar = callbackfn.call(thisArg, str[i], i, cur)
      const tmp = cur.children[retChar]
      if (!tmp || tmp.countPrefix <= 0) return
      cur = tmp
    }
  }

  /**
   * @description Search a string in the trie
   * @returns Number of `str` in the trie
   */
  count (str: string): number {
    let ans = 0
    this.traverse(str, (char, idx, node) => {
      const nextNode = node.children[char]
      if (idx === str.length - 1 && nextNode) {
        ans = nextNode.count
      }
      return char
    })
    return ans
  }

  /**
   * @description Search a string in the trie
   * @returns Number of prefix of `str` in the trie
   */
  countPrefix (str: string): number {
    let ans = 0
    this.traverse(str, (char, idx, node) => {
      const nextNode = node.children[char]
      ans += nextNode?.countPrefix ?? 0
      return char
    })
    return ans
  }
};

function sumPrefixScores (words: string[]): number[] {
  const trie = new Trie()
  const ans = []
  for (const w of words) {
    trie.insert(w, 1)
  }
  for (const w of words) {
    ans.push(trie.countPrefix(w))
  }
  return ans
};
