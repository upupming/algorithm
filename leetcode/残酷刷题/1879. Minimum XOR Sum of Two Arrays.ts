/*
f[i]: i 的二进制表示中 1 对应的 nums[1] 中的数已经和 nums[2] 中配对好，且所有配对顺序中 XOR Sum 最小的答案
转移: 枚举 nums2[j] (i>>j&1==1) 和 nums1[cnt_1(i)-1] 配对，取最大值即可
时间复杂度: O(n 2^n)
*/
function minimumXORSum (nums1: number[], nums2: number[]): number {
  const n = nums1.length
  const f = Array<number>(1 << n).fill(1e10)
  f[0] = 0
  for (let i = 1; i < 1 << n; i++) {
    let cnt = 0
    for (let k = 0; k < n; k++) cnt += i >> k & 1
    for (let k = 0; k < n; k++) {
      if (i >> k & 1) {
        f[i] = Math.min(f[i], f[i - (1 << k)] + (nums2[k] ^ nums1[cnt - 1]))
      }
    }
  }
  return f[(1 << n) - 1]
};
