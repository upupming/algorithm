/**
 * @param {number[]} stones
 * @return {boolean}
 */
const stoneGameIX = function (stones) {
  const cnt = [0, 0, 0]
  const n = stones.length
  for (const s of stones) {
    cnt[s % 3]++
  }
  const calcLen = (a, b) => {
    if (a >= 2) return 2 + (a - 2 >= b ? 2 * b : 2 * (a - 2) + 1) + cnt[0]
    else return a + cnt[0]
  }
  // 11212...
  const len1 = calcLen(cnt[1], cnt[2])
  // 22121...
  const len2 = calcLen(cnt[2], cnt[1])
  if (len1 > cnt[0] && len1 % 2 === 1 && len1 < n) return true
  if (len2 > cnt[0] && len2 % 2 === 1 && len2 < n) return true
  return false
}
/*
[5,11,12,1,4,5,3]
[2,3,2,2,2,3,3,2,1]
[1,1,7,10,8,17,10,20,2,10]
*/
