/**
 * @param {number} numOnes
 * @param {number} numZeros
 * @param {number} numNegOnes
 * @param {number} k
 * @return {number}
 */
const kItemsWithMaximumSum = function (numOnes, numZeros, numNegOnes, k) {
  let s = 0
  while (k--) {
    if (numOnes > 0) s += 1, numOnes -= 1
    else if (numZeros > 0) numZeros -= 1
    else if (numNegOnes > 0) s -= 1, numNegOnes -= 1
  }
  return s
}
