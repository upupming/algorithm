/**
 * @param {number[]} candidates
 * @return {number}
 */
const largestCombination = function (cs) {
  let ans = 0
  for (let i = 31; i >= 0; i--) {
    let cnt = 0
    for (const s of cs) {
      if (s >> i & 1) cnt++
    }
    ans = Math.max(ans, cnt)
  }
  return ans
}
