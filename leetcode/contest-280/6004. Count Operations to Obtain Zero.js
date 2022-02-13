/**
 * @param {number} num1
 * @param {number} num2
 * @return {number}
 */
var countOperations = function (num1, num2) {
  if (num1 === 0 || num2 === 0) return 0
  if (num1 > num2) return countOperations(num1 - num2, num2) + 1
  else return countOperations(num1, num2 - num1) + 1
}
