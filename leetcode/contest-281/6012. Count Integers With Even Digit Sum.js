/**
 * @param {number} num
 * @return {number}
 */
const countEven = function (num) {
  let ans = 0
  for (let x = 1; x <= num; x++) {
    let c = 0; let y = x
    while (y) {
      c += y % 10
      y = Math.floor(y / 10)
    }
    // console.log(x, c)
    if (c % 2 === 0) ans++
  }
  return ans
}
