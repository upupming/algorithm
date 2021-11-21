/**
 * @param {number[]} colors
 * @return {number}
 */
const maxDistance = function (c) {
  const n = c.length
  let ans = 0
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      if (c[i] !== c[j]) ans = Math.max(ans, j - i)
    }
  }
  return ans
}
