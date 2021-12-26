/**
 * @param {number} num
 * @return {boolean}
 */
 var isSameAfterReversals = function(num) {
  const r = (num) => Number(String(num).split('').reverse().join(''))
  return r(r(num)) === num
};