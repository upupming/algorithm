/**
 * @param {number} mass
 * @param {number[]} asteroids
 * @return {boolean}
 */
 var asteroidsDestroyed = function(m, a) {
  a.sort((a, b) => a - b)
  for (const x of a) {
      if (m < x) return false
      m += x
  }
  return true
};
