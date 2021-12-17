/**
 * @param {string} rings
 * @return {number}
 */
const countPoints = function (ri) {
  const r = ri.split('')
  const cnt = []
  for (let i = 0; i < r.length; i += 2) {
    const c = r[i]; const l = Number(r[i + 1])
    if (!cnt[l]) cnt[l] = new Set()
    cnt[l].add(c)
  }
  let ans = 0
  for (const s of cnt) {
    if (s?.size >= 3) ans++
  }
  return ans
}
