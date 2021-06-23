/*
由于只有 100 个数
用 cntSum[i][j] 表示数 i 在 1~j 出现的次数，直接用前缀和即可解决问题
*/
function minDifference (nums: number[], queries: number[][]): number[] {
  const [n, m] = [nums.length, queries.length]
  const cntSum: number[][] = [...Array(110)].map(() => Array(n).fill(0)
  )
  for (let i = 1; i <= 100; i++) {
    for (let j = 1; j <= n; j++) {
      cntSum[i][j] = cntSum[i][j - 1] + Number(nums[j - 1] === i)
    }
  }
  const ans = []
  for (let i = 0; i < m; i++) {
    let tmp = 110
    const q = queries[i]
    let last = -1
    for (let a = 1; a <= 100; a++) {
      // [q[0], q[1]] 区间内是否有数 a
      if (cntSum[a][q[1] + 1] - cntSum[a][q[0]]) {
        if (last !== -1) {
          tmp = Math.min(tmp, a - last)
        }
        last = a
      }
    }
    ans[i] = tmp === 110 ? -1 : tmp
  }
  return ans
};
