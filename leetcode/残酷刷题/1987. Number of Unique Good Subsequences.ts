function numberOfUniqueGoodSubsequences (binary: string): number {
  const last = []; const dp = []; const P = 1e9 + 7
  dp[-1] = 0
  for (let i = 0; i < binary.length; i++) {
    if (binary[i] === '0' && last['1'] === undefined) dp[i] = 0
    else {
      if (last['1'] === undefined) dp[i] = 1
      else dp[i] = (dp[i - 1] * 2 - ((last[binary[i]] === undefined) ? 0 : dp[last[binary[i]] - 1]) + P) % P
    }
    last[binary[i]] = i
  }
  return (dp.pop()! + Number(last['0'] !== undefined)) % P
};
