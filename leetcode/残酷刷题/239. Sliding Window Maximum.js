/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
const maxSlidingWindow = function (nums, k) {
  const q = []; const ans = []
  for (let i = 0; i < nums.length; i++) {
    // 越远，又越小的数不需要保留
    while (q.length && q[q.length - 1][0] < nums[i]) q.pop()
    q.push([nums[i], i])
    // 长度不能超过 k
    while (q.length && i - q[0][1] >= k) q.shift()
    if (i >= k - 1) ans.push(q[0][0])
  }
  return ans
}
