/*
5 2 15
3 -7 8 -5 9

12
*/
let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

process.on('SIGINT', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const [n, m, k] = s[0].split(' ').map(Number)
  const a = s[1].split(' ').map(BigInt)

  // const cnt = []; const sum = []
  // cnt[-1] = 0
  // sum[-1] = 0n
  // for (let i = 0; i < n; i++) {
  //   cnt[i] = cnt[i - 1] + ((a[i] < 0) ? 1 : 0)
  //   sum[i] = sum[i - 1] + a[i]
  // }

  // let ans = 0n
  // for (let i = 0; i < n; i++) {
  //   for (let j = i; j < n; j++) {
  //     const sumS = sum[j] - sum[i - 1]
  //     const cntS = cnt[j] - cnt[i - 1]
  //     if (cntS <= m && sumS <= k) {
  //       if (ans < sumS) ans = sumS
  //     } else break
  //   }
  // }
  // console.log(String(ans))

  // left 表示滑窗左端点
  let sum = 0n; let cntNegative = 0; let left = 0
  let ans = 0n
  for (let i = 0; i < n; i++) {
    cntNegative += (a[i] < 0) ? 1 : 0
    sum += a[i]
    if (left === -1) left = i

    // 负数太多，就把左边界往右移
    while (cntNegative > m) {
      sum -= a[left]
      if (a[left] < 0n) cntNegative--
      left++
      if (left > i) left = -1
    }
    // 总和小于 0，不如重新开始
    if (sum <= 0) {
      sum = 0n
      cntNegative = 0
      left = -1
    }
    // console.log(left, i, sum)
    if (sum <= k && ans < sum) ans = sum
  }
  // 最后左边界可以往右收缩
  while (left !== -1 && left < n) {
    sum -= a[left++]
    // console.log(left, sum)
    if (sum <= k && ans < sum) ans = sum
  }
  console.log(Number(ans))
}
