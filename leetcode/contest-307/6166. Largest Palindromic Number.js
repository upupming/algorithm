/**
 * @param {string} num
 * @return {string}
 */
const largestPalindromic = function (num) {
  const cnt = Array(10).fill(0)
  String(num).split('').forEach(x => {
    cnt[Number(x)]++
  })
  // 1. 如果只有 0 的话
  // 2. 否则的话
  const ans = []; let rest = -1
  let has = false
  for (let i = 9; i >= 0; i--) {
    if (i === 0 && !has) return '0'
    if (!ans.length && i === 0) break
    if (cnt[i] > 0) has = true
    while (cnt[i] >= 2) {
      ans.push(i)
      cnt[i] -= 2
    }
    if (cnt[i] && rest === -1) rest = i
  }
  if (rest !== -1) return ans.join('') + rest + [...ans].reverse().join('')
  return ans.join('') + [...ans].reverse().join('')
}
