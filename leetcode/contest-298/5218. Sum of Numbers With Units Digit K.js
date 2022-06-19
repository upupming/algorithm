/**
 * @param {number} num
 * @param {number} k
 * @return {number}
 */
const map = {}
var minimumNumbers = function (num, k) {
  if (map[`${num}_${k}`] != null) return map[`${num}_${k}`]
  // console.log(num, k)
  if (num === 0) return 0
  if (num < k) return -1
  let ans = 1e10
  // 枚举最后一个数
  for (let i = 1; i <= num; i++) {
    if (i % 10 === k) {
      const prev = minimumNumbers(num - i, k)
      if (prev === -1) continue
      else ans = Math.min(ans, prev + 1)
    }
  }
  return map[`${num}_${k}`] = (ans === 1e10 ? -1 : ans)
}
