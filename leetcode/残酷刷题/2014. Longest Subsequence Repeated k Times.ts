function longestSubsequenceRepeatedK (s: string, k: number): string {
  const cnt = Array<number>(26).fill(0)
  for (let i = 0; i < s.length; i++) {
    cnt[s[i].charCodeAt(0) - 'a'.charCodeAt(0)] += 1
  }
  // c.length <= 7
  const c = new Map<number, number>()
  for (let i = 0; i < 26; i++) {
    if (cnt[i] >= k) c.set(i, cnt[i])
  }
  let allowed = ''; let curSeq = ''; let ans = ''
  for (const ch of s) if (c.has(ch.charCodeAt(0) - 'a'.charCodeAt(0))) allowed += ch
  dfs()
  return ans
  // O(t)
  function cntTimes (s: string, t: string) {
    let times = 0; let pos = 0
    for (const ch of t) {
      if (ch === s[pos]) {
        pos++
        if (pos === s.length) {
          times++; pos = 0
        }
      }
    }
    return times
  }
  // 枚举 c 中字符所有排列，O(7!)，每个结果需要和 allowed 比对，O(n=16000)
  function dfs () {
    const c1 = new Map(c)
    for (const [ch, cnt] of c1.entries()) {
      curSeq += String.fromCharCode(ch + 'a'.charCodeAt(0))
      if (curSeq.length > ans.length || (curSeq.length === ans.length && curSeq > ans)) {
        if (cntTimes(curSeq, allowed) >= k) ans = curSeq
      }
      c.set(ch, cnt - k)
      if (c.get(ch)! < k) c.delete(ch)
      dfs()
      curSeq = curSeq.slice(0, -1)
      c.set(ch, cnt)
    }
  }
};
