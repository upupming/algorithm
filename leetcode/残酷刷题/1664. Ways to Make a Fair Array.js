/**
 * @param {number[]} nums
 * @return {number}
 */
const waysToMakeFair = function (nums) {
  const n = nums.length
  const lOdd = []; const rOdd = []; const lEven = []; const rEven = []
  for (let i = 0; i < n; i++) {
    lEven[i] = (lEven[i - 1] ?? 0) + ((i % 2 === 0) ? nums[i] : 0)
    lOdd[i] = (lOdd[i - 1] ?? 0) + ((i % 2 === 1) ? nums[i] : 0)
  }
  for (let i = n - 1; i >= 0; i--) {
    rEven[i] = (rEven[i + 1] ?? 0) + ((i % 2 === 0) ? nums[i] : 0)
    rOdd[i] = (rOdd[i + 1] ?? 0) + ((i % 2 === 1) ? nums[i] : 0)
  }
  // console.log(lEven, lOdd, rEven, rOdd)
  let ans = 0
  for (let i = 0; i < n; i++) {
    const odd = (lOdd[i - 1] ?? 0) + (rEven[i + 1] ?? 0)
    const even = (lEven[i - 1] ?? 0) + (rOdd[i + 1] ?? 0)
    // console.log(i, odd, even)
    if (odd === even) ans++
  }
  return ans
}
