/**
 * @param {string} s
 * @return {number}
 */
const partitionString = function (s) {
  const n = s.length
  let ans = 0
  for (let i = 0; i < n;) {
    ans++
    const c = new Set()
    let j = i
    while (j < n && !c.has(s[j])) c.add(s[j++])
    i = j
  }
  return ans
}
