/*
目标只有这几种情况
0101...01
1010...10
[0101...0][10...10]
[1010...1][01...01]

[0101...0][01...01]（中间出现了 00 连接，可以使用 type 1 让新的串从这里断开）
[1010...1][10...10]
*/
function minFlips (s: string): number {
  const n = s.length
  const l = Array<number[]>(2).fill([]).map(() => Array<number>(n).fill(0))
  const r = Array<number[]>(2).fill([]).map(() => Array<number>(n).fill(0))
  for (let j = 0; j < 2; j++) {
    for (let i = 0, c = 0, k = j; i < n; i++, k ^= 1) {
      if (s.charCodeAt(i) - '0'.charCodeAt(0) !== k) c++
      l[j][i] = c
    }
    for (let i = n - 1, c = 0, k = j; i >= 0; i--, k ^= 1) {
      if (s.charCodeAt(i) - '0'.charCodeAt(0) !== k) c++
      r[j][i] = c
    }
  }

  let ans = 1e6
  ans = Math.min(ans, l[0][n - 1], l[1][n - 1])
  for (let i = 0; i + 1 < n; i++) {
    ans = Math.min(ans, l[0][i] + r[1][i + 1], l[1][i] + r[0][i + 1])
  }
  return ans
};
