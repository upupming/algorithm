/**
 * @param {number} n
 * @return {number}
 */
const smallestEvenMultiple = function (n) {
  if (n % 2 === 0) return n
  return 2 * n
}
