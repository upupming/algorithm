/**
 * @param {number[]} nums
 * @param {number} goal
 * @return {number}
 */
const numSubarraysWithSum = function (nums, goal) {
  const n = nums.length
  let s = 0; let ans = 0; let last = 0
  for (let i = 0, j = 0; i < n; i++) {
    let cnt = 0
    while (j < n && (s + nums[j]) <= goal) {
      s += nums[j]
      if (j >= i) cnt += s === goal
      j++
    }
    if (i - 1 >= 0 && nums[i - 1] === 0) cnt = last - (nums[i - 1] === goal)
    // console.log(i, j, cnt, last)
    ans += cnt
    last = cnt
    s -= nums[i]
  }
  return ans
}
