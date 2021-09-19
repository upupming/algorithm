/**
 * @param {string[]} operations
 * @return {number}
 */
 var finalValueAfterOperations = function(operations) {
  let x = 0
  operations.forEach(o => (o === "X++" || o === "++X") ? x++ : x--)
  return x
};