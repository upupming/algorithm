function recoverArray (n: number, sums: number[]): number[] {
  sums.sort((a, b) => a - b)
  const ans: number[] = []
  dfs(sums, n)
  return ans
  // sums 已经排好序了
  function dfs (sums: number[], n: number): boolean {
    if (sums.length === 2) {
      if (sums[0] !== 0 && sums[1] !== 0) return false
      ans.push(sums[0] ? sums[0] : sums[1])
      return true
    }
    const [a, b] = [sums[sums.length - 1], sums[sums.length - 2]]
    const x = a - b
    const getSums1 = (x: number) => {
      const toDelete: number[] = []
      const sums1 = []
      let [start, end, step] = [0, sums.length - 1, 1]
      // x < 0，需要从大到小遍历
      if (x < 0) [start, end, step] = [sums.length - 1, 0, -1]
      for (let i = start; i !== end; i += step) {
        const s = sums[i]
        if (toDelete[s]) {
          toDelete[s]--
          continue
        }
        sums1.push(s)
        toDelete[s + x] ??= 0; toDelete[s + x]++
      }
      return x < 0 ? sums1.reverse() : sums1
    }
    ans.push(x)
    if (dfs(getSums1(x), n - 1)) return true
    ans.pop()
    ans.push(-x)
    if (dfs(getSums1(-x), n - 1)) return true
    ans.pop()
    return false
  }
};
