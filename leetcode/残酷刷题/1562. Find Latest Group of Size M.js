/**
 * @param {number[]} arr
 * @param {number} m
 * @return {number}
 */
const findLatestStep = function (arr, m) {
  const day = []; const n = arr.length; const q = []
  let ans = -1
  for (let i = 0; i < arr.length; i++) {
    day[arr[i]] = i + 1
  }
  // 区间 [i-m+1, i] 被设置为 1，求区间中所有 1 的最大 day 值
  for (let i = 1; i <= n; i++) {
    while (q.length && i - q[0][1] >= m) q.shift()
    while (q.length && q[q.length - 1][0] <= day[i]) q.pop()
    q.push([day[i], i])

    if (i < m) continue
    const maxDay = q[0][0]
    const left = day[i - m] ?? 1e10; const right = day[i + 1] ?? 1e10
    if (left > maxDay && right > maxDay) {
      ans = Math.max(ans, Math.min(left, right, n + 1) - 1)
    }
  }
  return ans
}
