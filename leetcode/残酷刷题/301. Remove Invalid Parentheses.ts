function removeInvalidParentheses (s: string): string[] {
  let [cnt, remove] = [0, 0]
  for (const ch of s) {
    if (ch === '(') cnt++
    else if (ch === ')') cnt--
    if (cnt < 0) {
      remove++
      cnt = 0
    }
  }
  remove += cnt
  const maxLen = s.length - remove
  const ans: string[] = []
  dfs(s, 0, '', 0)
  return ans

  function dfs (s: string, idx: number, curStr: string, cnt: number) {
    // 多出右括号，提前剪枝
    if (cnt < 0) return
    if (curStr.length > maxLen) return
    if (idx === s.length) {
      if (curStr.length === maxLen && cnt === 0) {
        ans.push(curStr)
      }
      return
    }

    if (s[idx] !== '(' && s[idx] !== ')') {
      return dfs(s, idx + 1, curStr + s[idx], cnt)
    }

    // 避免重复搜索
    // 当前括号和上一个填的不同，可填可不填
    if (curStr.length === 0 || curStr[curStr.length - 1] !== s[idx]) {
      // 填
      dfs(s, idx + 1, curStr + s[idx], cnt + (s[idx] === '(' ? 1 : -1))
      // 不填
      dfs(s, idx + 1, curStr, cnt)
    } else {
      // 相同，必须填
      dfs(s, idx + 1, curStr + s[idx], cnt + (s[idx] === '(' ? 1 : -1))
    }
  }
};
