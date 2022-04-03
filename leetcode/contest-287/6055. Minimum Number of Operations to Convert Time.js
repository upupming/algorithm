/**
 * @param {string} current
 * @param {string} correct
 * @return {number}
 */
const convertTime = function (a, b) {
  const t = (x) => {
    const [m, n] = x.split(':').map(Number)
    return m * 60 + n
  }
  let ta = t(a)
  let tb = t(b)
  if (ta > tb) tb += 24 * 60
  let ans = 0
  while (ta < tb) {
    if (ta + 60 <= tb) ta += 60
    else if (ta + 15 <= tb) ta += 15
    else if (ta + 5 <= tb) ta += 5
    else if (ta + 1 <= tb) ta += 1
    ans++
  }
  return ans
}
