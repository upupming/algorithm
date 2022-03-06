/**
 * @param {string} s
 * @return {string[]}
 */
const cellsInRange = function (s) {
  const [x, y] = s.split(':')
  const ans = []
  for (let a = x[0]; a <= y[0]; a = String.fromCharCode(a.charCodeAt(0) + 1)) {
    for (let b = x[1]; b <= y[1]; b = String.fromCharCode(b.charCodeAt(0) + 1)) {
      ans.push(a + b)
    }
  }
  return ans
}
