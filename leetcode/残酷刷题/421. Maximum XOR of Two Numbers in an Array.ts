class Trie {
  m: number
  trie: number[][]
  /* Count of a node */
  cnt: number[]
  /* Number of nodes in the trie */
  tot: number
  s: number
  /**
   * @description Initialize the trie
   * @param m the range of the chars
   * @param s the smallest char in the string, assuming all chars are in range [s, s+m)
   */
  constructor (m: number, s = 'a') {
    this.m = m
    this.trie = [[]]
    this.cnt = []
    // Node 1 is the root node
    this.tot = 1
    this.s = s.charCodeAt(0)
  }

  /**
   * @description Insert strings into the trie
   * @param x the string to be inserted
   * @param t number of `x` to be inserted, can be negative for deleting x from the trie
   */
  insert (x: string, t: number = 1) {
    let p = 1
    for (let i = 0; i < x.length; i++) {
      const idx = x.charCodeAt(i) - this.s
      this.trie[p] ??= Array(this.m).fill(0)
      if (this.trie[p][idx] === 0) {
        this.trie[p][idx] = ++this.tot
      }
      p = this.trie[p][idx]
      this.cnt[p] ??= 0
      this.cnt[p] += t
    }
  }

  /**
   * @description Search a string in the trie
   * @returns Number of `x` in the trie
   */
  search (x: string) {
    let p = 1
    for (let i = 0; i < x.length; i++) {
      const idx = x.charCodeAt(i) - this.s
      if (this.trie[p][idx] === 0) {
        return 0
      }
      p = this.trie[p][idx]
    }
    return this.cnt[p]
  }

  /**
   * @description Search a string in the trie
   * @returns Number prefix of `x` in the trie
   */
  searchPrefix (x: string) {
    let p = 1
    let ans = 0
    for (let i = 0; i < x.length; i++) {
      const idx = x.charCodeAt(i) - this.s
      if (this.trie[p][idx] === 0) {
        return ans
      }
      p = this.trie[p][idx]
      ans += this.cnt[p]
    }
    return ans
  }

  /**
   * @description Search a string in the trie
   * @returns Maximum XOR of `x` in the trie
   */
  searchMaxXor (x: string) {
    let p = 1
    const ans = []
    for (let i = 0; i < x.length; i++) {
      const idx = x.charCodeAt(i) - this.s
      // Go in opposite direction as possible
      if (this.cnt[this.trie[p][this.m - 1 - idx]]) {
        p = this.trie[p][this.m - 1 - idx]
        ans.push(this.s + this.m - 1 - idx)
      } else {
        p = this.trie[p][idx]
        ans.push(this.s + idx)
      }
    }
    return String.fromCharCode(...ans)
  }
};

function findMaximumXOR (nums: number[]): number {
  const s = nums.map(num => num.toString(2).padStart(32, '0'))
  const trie = new Trie(2, '0')
  s.forEach(trie.insert, trie)
  let ans = 0
  s.map(trie.searchMaxXor, trie).forEach((x, idx) => { ans = Math.max(ans, parseInt(x, 2) ^ nums[idx]) })
  return ans
};
