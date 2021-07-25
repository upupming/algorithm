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

// https://leetcode-cn.com/problems/delete-duplicate-folders-in-system/solution/zi-dian-shu-ha-xi-biao-by-endlesscheng-115r/
function deleteDuplicateFolder (paths: string[][]): string[][] {
  const trie = new Trie()
  for (const path of paths) {
    let cur = trie.trie
    cur.countPrefix++
    for (const name of path) {
      cur.children[name] ??= new TrieNode(name)
      cur = cur.children[name]!
      cur.countPrefix++
    }
  }
  // 目录的子结构的哈希，映射到有哪些目录都是这个哈希值
  const folders = new Map<string, TrieNode[]>()
  dfs1(trie.trie)
  for (const value of folders.values()) {
    if (value.length > 1) {
      // 出现了一样的目录，全部标记问删除
      for (const node of value) {
        node.countPrefix = 0
      }
    }
  }
  const ans: string[][] = []
  // 遍历一遍没有删除的目录，把它们放到答案中
  dfs2(trie.trie, [])
  return ans
  function dfs1 (node: TrieNode): string {
    if (Object.keys(node.children).length === 0) {
      return `(${node.char})`
    }
    const childrenExp: string[] = []
    for (const key in node.children) {
      childrenExp.push(dfs1(node.children[key]!))
    }
    const exp = childrenExp.sort((a, b) => a.localeCompare(b)).join('')
    if (!folders.has(exp)) {
      folders.set(exp, [])
    }
    folders.get(exp)!.push(node)
    return `(${node.char}${childrenExp.join('')})`
  }
  function dfs2 (node: TrieNode, path: string[]) {
    // 已经被删除的节点，不需要再往下访问了
    if (node.countPrefix === 0) {
      return
    }
    if (node.char !== '/') { path.push(node.char) }
    if (path.length) ans.push([...path])
    for (const key in node.children) {
      dfs2(node.children[key]!, path)
    }
    path.pop()
  }
};
