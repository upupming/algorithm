/**
 * @param {number[]} nums
 * @return {number}
 */
const subArrayRanges = function (nums) {
  const n = nums.length
  let ans = 0n
  for (let i = 0; i < n; i++) {
    // 作为最大值的次数
    let j = i - 1; let k = i + 1
    while (j >= 0 && nums[j] <= nums[i]) j--
    while (k < n && nums[k] < nums[i]) k++
    const cnt1 = k - j - 1 + (i - j - 1) * (k - i - 1)
    let x = i - 1; let y = i + 1
    while (x >= 0 && nums[x] > nums[i]) x--
    while (y < n && nums[y] >= nums[i]) y++
    const cnt2 = y - x - 1 + (i - x - 1) * (y - i - 1)
    // console.log(i, nums[i], cnt1, cnt2)
    ans += BigInt((cnt1 - cnt2) * nums[i])
  }
  return Number(ans)
}
