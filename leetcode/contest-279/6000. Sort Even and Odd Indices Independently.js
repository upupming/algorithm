/**
 * @param {number[]} nums
 * @return {number[]}
 */
const sortEvenOdd = function (nums) {
  const a = []; const b = []
  const n = nums.length
  for (let i = 0; i < n; i++) {
    if (i % 2) a.push(nums[i])
    else b.push(nums[i])
  }
  b.sort((a, b) => a - b)
  a.sort((a, b) => -(a - b))
  // console.log(a, b)
  const ans = []
  while (a.length || b.length) {
    if (b.length) ans.push(b.shift())
    if (a.length) ans.push(a.shift())
  }
  return ans
}
