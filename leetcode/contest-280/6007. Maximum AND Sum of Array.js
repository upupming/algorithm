/**
 * @param {number[]} nums
 * @param {number} numSlots
 * @return {number}
 */
const maximumANDSum = function (nums, numSlots) {
  const f = Array(1 << 2 * numSlots).fill(0)
  let ans = 0
  for (let i = 0; i < f.length; i++) {
    let cnt = 0; let t = i
    while (t) cnt += t & 1, t >>= 1
    // 前 cnt 个数字放到篮子中，最大与和
    if (cnt >= nums.length) continue
    // 枚举下一个位置 j，如果 j 没有放数的话
    for (let j = 0; j < 2 * numSlots; j++) {
      if ((i >> j & 1) === 0) {
        const s = i | (1 << j)
        const x = Math.floor((j + 2) / 2)
        f[s] = Math.max(f[s], f[i] + (x & nums[cnt]))
        ans = Math.max(ans, f[s])
      }
    }
  }
  return ans
}
