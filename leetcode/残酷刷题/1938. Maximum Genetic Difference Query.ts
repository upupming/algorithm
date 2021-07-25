// dfs 题中给的树的时候，动态维护 trie 树，对答案进行更新
export {}
class TrieNode {
  count: number = 0
  countPrefix: number = 0
  children: { [key: string]: TrieNode | undefined } = {}
};

class Trie {
  readonly trie: TrieNode
  /**
   * @description Initialize the trie
   */
  constructor () {
    this.trie = new TrieNode()
  }

  /**
   * @description Insert strings into the trie
   * @param str the string to be inserted
   * @param count number of `str` to be inserted, can be negative for deleting x from the trie
   */
  insert (str: string, count: number = 1): void {
    let cur = this.trie
    for (const char of str) {
      cur.children[char] ??= new TrieNode()
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

function maxGeneticDifference (parents: number[], queries: number[][]): number[] {
  const map = new Map<number, any[]>()
  for (let i = 0; i < queries.length; i++) {
    const key = queries[i][0]
    const value = queries[i][1]
    if (!map.has(key)) {
      map.set(key, [])
    }
    map.get(key)!.push({
      val: value,
      index: i
    })
  }
  const n = parents.length
  const e: number[][] = [...Array(n)].map(() => [])
  let root = -1
  for (let i = 0; i < n; i++) {
    if (parents[i] === -1) root = i
    else { e[parents[i]].push(i) }
  }

  const trie = new Trie()
  const ans: number[] = []
  dfs(root)
  return ans
  function maxXor (str: string): number {
    const reverse = (ch: string): string => ch === '1' ? '0' : '1'
    let tmp = 0
    trie.traverse(str, (char, idx, node) => {
      tmp <<= 1
      if (node.children[reverse(char)]?.countPrefix) {
        tmp += 1
        return reverse(char)
      } else {
        return char
      }
    })
    return tmp
  }
  function dfs (x: number): void {
    const str = x.toString(2).padStart(32, '0')
    trie.insert(str, 1)
    if (map.has(x)) {
      for (const { index, val } of map.get(x)!) {
        ans[index] = maxXor(val.toString(2).padStart(32, '0'))
      }
    }
    for (let i = 0; i < e[x].length; i++) {
      dfs(e[x][i])
    }
    trie.insert(str, -1)
  }
};
