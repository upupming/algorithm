/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var countPartitions = function(nums, k) {
  const n = nums.length, s = nums.reduce((p, c) => p+c, 0)
  const dp = Array(n).fill(0).map(() => Array(k).fill(0))
  dp[0][0] = 1, dp[0][nums[0]] = 1
  let P = 1e9+7
  // s>=2k
  if (s<2*k) return 0
  for (let i = 1; i < n; i++) {
      for (let l = 0; l < k; l++) {
          // 前 i 个元素，构成和 l 的方案数
          dp[i][l] = (dp[i-1][l] + ((l-nums[i]>=0) ? dp[i-1][l-nums[i]] : 0))%P
      }
  }
  let qpow = (a, b, p = P) => {
      let ans = 1%p
      while (b) {
          if (b&1) ans = Number(BigInt(ans)*BigInt(a)%BigInt(p))
          a = Number(BigInt(a)*BigInt(a)%BigInt(p))
          b>>=1
      }
      return ans
  }
  let t = 0
  for (let i = 0; i < k; i++) t += dp[n-1][i], t %= P
  return ((qpow(2, n) - t - t)%P+P)%P
};
