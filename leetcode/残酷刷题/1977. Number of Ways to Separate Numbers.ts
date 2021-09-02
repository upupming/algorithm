// dp[i][l]: 以 i 结尾，最后一个数长度为 len 的方案数
// dpSum[i][l]: sum(dp[i][1], dp[i][2], ..., dp[i][i+1]), num[j...i], num[j] !== '0'
function numberOfCombinations (num: string): number {
  const n = num.length
  const P = 1e9 + 7
  const dpSum = [...Array(n)].map(() => Array<number>(n + 1).fill(0))
  const lcs = [...Array(n + 1)].map(() => new Uint16Array(n + 1).fill(0))
  for (let i = n - 1; i >= 0; i--) {
    for (let j = n - 1; j >= 0; j--) {
      lcs[i][j] = num[i] === num[j] ? (lcs[i + 1][j + 1] + 1) : 0
    }
  }
  for (let i = 0; i < n; i++) {
    for (let l = 1; l <= i + 1; l++) {
      let dp = 0
      let [j, k] = [i - l + 1, i - 2 * l + 1]
      k = Math.max(k, 0)
      // 暴力
      // if (j - k === l && num.slice(k, j) > num.slice(j, i + 1)) k++
      // lcs 优化
      if (j - k === l && lcs[k][j] < l && num[k + lcs[k][j]] > num[j + lcs[k][j]]) k++
      // 长度分别是 j-k, j-k-1, ..., 1
      dp = j - 1 >= 0 ? dpSum[j - 1][j - k] : 1
      // 如果是前导 0 不需要
      if (num[j] === '0') dp = 0
      dpSum[i][l] = (dpSum[i][l - 1] + dp) % P
    }
  }
  return dpSum[n - 1][n]
};
