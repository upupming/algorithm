/**
 * @param {number[]} derived
 * @return {boolean}
 */
const doesValidArrayExist = function (d) {
  let c = 0
  for (const x of d) {
    c ^= x
  }
  return c === 0
}
