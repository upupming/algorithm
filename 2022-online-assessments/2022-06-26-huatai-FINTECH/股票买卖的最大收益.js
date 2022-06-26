let input = ''

process.stdin.on('data', data => input += data)

process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [n, k, x] = lines[0].split(' ').map(Number)
  const a = lines[1].split(' ').map(Number)
  const dp = []
  // 0: 不操作,1: 卖出,2: 买入
  dp[0] = [null, [x, 0], [0, 0]]
  for (let i = 1; i <= n; i++) {
    dp[i] = []
    let idx = -1, maxV = -1
    for (let j = 1; j < 3; j++) {
      const v = dp[i-1][j][0] * a[i-1] + dp[i-1][j][1]
      if(v > maxV) {
        idx = j
        maxV = v
      }
    }
    dp[i][1] = [0, maxV]
    let ck = Math.min(Math.floor(maxV / a[i-1]), k)
    dp[i][2] = [ck, maxV - a[i-1] * ck]
  }
  let ans = 0
//   console.log(dp)
  for (let j = 1; j < 3; j++) {
    const v = dp[n][j][0] * a[n-1] + dp[n][j][1]
    ans = Math.max(ans, v)
  }
  console.log(ans)
})
