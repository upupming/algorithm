// dp[i]: s[0:i] 中的满足条件的子集，可以有空串，不一定以 s[i] 结尾
// dp[i] 中分以 s[i] 结尾的和不以 s[i] 结尾的两种情况讨论即可
// 不以 s[i] 结尾: dp[i-1]
// 以 s[i] 结尾: dp[i-1] - dp[j-1]，其中 j 为最近的一个 s[j] == s[i]
function distinctSubseqII (s: string): number {
  const last = []; const dp = [2]; const P = 1e9 + 7
  last[s[0]] = 0, dp[-1] = 1
  for (let i = 1; i < s.length; i++) {
    dp[i] = (dp[i - 1] * 2 - (last[s[i]] === undefined ? 0 : dp[last[s[i]] - 1]) + P) % P
    last[s[i]] = i
  }
  return dp.pop()! - 1
};
