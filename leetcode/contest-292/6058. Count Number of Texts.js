const P = 1e9 + 7
const dp3 = [1]; const dp4 = [1]
for (let i = 1; i < 1e5 + 10; i++) {
  dp3[i] = ((dp3[i - 1] ?? 0) + (dp3[i - 2] ?? 0) + (dp3[i - 3] ?? 0)) % P
  dp4[i] = ((dp4[i - 1] ?? 0) + (dp4[i - 2] ?? 0) + (dp4[i - 3] ?? 0) + (dp4[i - 4] ?? 0)) % P
}

/**
 * @param {string} pressedKeys
 * @return {number}
 */
const countTexts = function (pk) {
  const n = pk.length
  let ans = 1
  for (let i = 0; i < n;) {
    let j = i; const ch = pk[i]
    while (j < n && pk[j] === ch) {
      j++
    }
    // console.log(i, j, j-i, dp[j-i])
    const dp = '79'.includes(ch) ? dp4 : dp3
    ans = Number((BigInt(ans) * BigInt(dp[j - i])) % BigInt(P))
    i = j
  }
  return ans
}
