/**
 * @param {number[][]} grid
 * @return {number}
 */
const maxTrailingZeros = function (g) {
  const m = g.length
  const n = g[0].length
  // { c2: 前面的数, c5:, c10: 多少 0 }
  const el = (c) => {
    const com = Math.min(c.c2, c.c5)
    c.c2 -= com
    c.c5 -= com
    c.c10 += com
  }
  const mul = (a, b) => {
    const c = {
      c2: a.c2 + b.c2,
      c5: a.c5 + b.c5,
      c10: a.c10 + b.c10
    }
    el(c)
    return c
  }
  const div = (a, b) => {
    const c = {
      c2: a.c2 - b.c2,
      c5: a.c5 - b.c5,
      c10: a.c10 - b.c10
    }
    el(c)
    return c
  }
  const get = (c) => {
    cc = { c2: 0, c5: 0, c10: 0 }
    while (c % 2 === 0) {
      cc.c2++
      c /= 2
    }
    while (c % 5 === 0) {
      cc.c5++
      c /= 5
    }
    el(c)
    return cc
  }
  const sumR = []; const sumC = []
  for (let i = 0; i < m; i++) {
    sumR[i] = []
    sumR[i][-1] = get(1)
    for (let j = 0; j < n; j++) {
      sumR[i][j] = mul(sumR[i][j - 1], get(g[i][j]))
      // console.log(0, i, j, get(g[i][j]), sumR[i][j-1], sumR[i][j])
    }
  }
  for (let j = 0; j < n; j++) {
    sumC[j] = []
    sumC[j][-1] = get(1)
    for (let i = 0; i < m; i++) {
      sumC[j][i] = mul(sumC[j][i - 1], get(g[i][j]))
      // console.log('1', j, i, sumR[i][j])
    }
  }

  let ans = 0
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      // 列 [0, i]，行 [j+1, n-1)
      const tmp = mul(div(sumR[i][n - 1], sumR[i][j]), sumC[j][i])
      // 列 [0, i]，行 [0, j-1]
      const tmp1 = mul(sumR[i][j - 1], sumC[j][i])
      // 列 [i, m-1]，行 [0, j-1]
      const tmp2 = mul(sumR[i][j - 1], div(sumC[j][m - 1], sumC[j][i - 1]))
      // 列 [i, m-1]，行 [j+1, n-1)
      const tmp3 = mul(div(sumR[i][n - 1], sumR[i][j]), div(sumC[j][m - 1], sumC[j][i - 1]))
      ans = Math.max(ans, tmp.c10, tmp1.c10, tmp2.c10, tmp3.c10)
    }
  }
  return ans
}
