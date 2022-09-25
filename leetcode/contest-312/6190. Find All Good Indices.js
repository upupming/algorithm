/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
const goodIndices = function (nums, k) {
  const n = nums.length
  const ans = []
  const left = []; const right = []
  // nums[-1] = 1e10, nums[n] = 1e10
  for (let i = 0; i < n; i++) {
    left[i] = i
    let j = i + 1
    while (j < n && nums[j] <= nums[j - 1]) left[j] = i, j++
    i = j - 1
  }
  for (let i = n - 1; i >= 0; i--) {
    right[i] = i
    let j = i - 1
    while (j >= 0 && nums[j] <= nums[j + 1]) right[j] = i, j--
    i = j + 1
  }
  // console.log(left, right)
  for (let i = k; i < n - k; i++) {
    const a = i - 1; const b = i + 1
    // console.log(i, a, b, left[a], a-k, right[b], b+k, a-left[a]+1>=k&&right[b]-b+k>=k)
    if (a - left[a] + 1 >= k && right[b] - b + 1 >= k) ans.push(i)
  }
  return ans
}
