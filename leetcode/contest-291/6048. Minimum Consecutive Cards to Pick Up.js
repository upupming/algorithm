/**
 * @param {number[]} cards
 * @return {number}
 */
const minimumCardPickup = function (cards) {
  const h = {}; let ans = 1e10
  for (let i = 0; i < cards.length; i++) {
    const c = cards[i]
    // console.log(i, c, h)
    if (h[c] != null) ans = Math.min(ans, i - h[c] + 1)
    h[c] = i
  }
  return ans === 1e10 ? -1 : ans
}
