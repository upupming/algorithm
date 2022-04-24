let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

// 正解应该是 DP: dp[i][j]表示第i天持有j手的最大余额

function main () {
  const s = input.split('\n')
  const [n, m] = s[0].split(' ').map(Number)
  const a = s[1].split(' ').map(Number)

  const dp = Array(n + 1).fill(0).map(() => [])
  dp[0][0] = m
  if (m >= a[0]) dp[0][1] = m - a[0]
  for (let i = 1; i < n; i++) {
    for (let j = 0; ;j++) {
      if (dp[i - 1][j - 1] == null || dp[i - 1][j - 1] - a[i] < 0) break
      dp[i][j] = dp[i][j] || 0
      // 第 i 天是买入
      dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - 1] - a[i])
    }
    for (let j = 0; ;j++) {
      if (dp[i - 1][j + 1] == null || dp[i - 1][j + 1] - a[i] < 0) break
      dp[i][j] = dp[i][j] || 0
      // 第 i 天是卖出
      dp[i][j] = Math.max(dp[i][j], dp[i - 1][j + 1] - a[i])
    }
    // 不买不卖
    for (let j = 0; ;j++) {
      if (dp[i - 1][j] == null) break
      dp[i][j] = dp[i][j] || 0
      dp[i][j] = Math.max(dp[i][j], dp[i - 1][j])
    }
  }
  // console.log(dp)
  let ans = 0
  for (let j = 0; ;j++) {
    if (dp[n - 1][j] == null) break
    ans = Math.max(ans, dp[n - 1][j] + j * a[n - 1])
  }
  console.log(ans)
}

/*
3 100
10 9 8

100
*/
