/**
 * 二分
 * @param {number} n
 * @param {number} index
 * @param {number} maxSum
 * @return {number}
 */
const maxValue = function (n, index, maxSum) {
  let l = 0; let r = 1e9
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (valid(mid)) l = mid
    else r = mid - 1
  }
  function valid (x) {
    let sum = x
    // 下标 0~index-1: 分布 1, 1, ..., 1..., x-2, x-1
    const leftCnt = Math.min(index, x - 1); const leftRest = index - leftCnt
    sum += (x - 1 + x - leftCnt) * leftCnt / 2 + leftRest
    const rightCnt = Math.min(n - 1 - index, x - 1); const rightRest = n - 1 - index - rightCnt
    sum += (x - 1 + x - rightCnt) * rightCnt / 2 + rightRest
    return sum <= maxSum
  }
  return l
}
