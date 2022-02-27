/**
 * @param {number[][]} tires
 * @param {number} changeTime
 * @param {number} numLaps
 * @return {number}

https://leetcode-cn.com/problems/minimum-time-to-finish-the-race/solution/jie-he-xing-zhi-qiao-miao-dp-by-endlessc-b963/

 */
const minimumFinishTime = function (tires, changeTime, numLaps) {
  const MAX = 2e8
  const sum = Array(tires.length).fill(0)
  const min = Array(18).fill(MAX)
  for (let i = 1; i <= 17; i++) {
    for (let j = 0; j < tires.length; j++) {
      const [f, r] = tires[j]

      // 连续使用 i 次，第 j 个轮胎所需要的代价
      sum[j] = Math.min(sum[j] + f, MAX)
      // 连续使用 i 次，所有轮胎所需要的最小代价
      min[i] = Math.min(min[i], sum[j])

      tires[j][0] = f * r
    }
  }
  const f = Array(numLaps + 1).fill(MAX)
  f[0] = 0
  for (let i = 1; i <= numLaps; i++) {
    for (let j = 1; j <= 17 && j <= i; j++) {
      // 最后连续 j 圈都使用了同一个轮胎
      f[i] = Math.min(f[i], f[i - j] + min[j])
    }
    f[i] += changeTime
  }
  return f[numLaps] - changeTime
}
