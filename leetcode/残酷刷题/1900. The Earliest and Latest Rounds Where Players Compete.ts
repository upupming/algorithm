/*
dp[n][a][b]
状态不是每一个都需要用到，因此使用记忆化搜索会更优
*/
function create2DArray<T> (N: number, M: number, n: T): T[][] {
  // https://stackoverflow.com/a/39879146/8242705
  // `empty` will be skipped in `map`, so we need destruct & create an `undefined` array
  return [...Array(N)].map(() => Array(M).fill(n))
}

function create3DArray<T> (N: number, M: number, L: number, n: T): T[][][] {
  return [...Array(N)].map(() => create2DArray(M, L, n))
}
function earliestAndLatest (n: number, a: number, b: number): number[] {
  const dpMin = create3DArray(30, 30, 30, 0)
  const dpMax = create3DArray(30, 30, 30, 0)
  return dp(n, a, b)
  function dp (n: number, a: number, b: number): number[] {
    // 注意下标从 1 开始
    if (a + b === n + 1) return [1, 1]
    if (dpMin[n][a][b]) return [dpMin[n][a][b], dpMax[n][a][b]]

    if (a > b) return dp(n, b, a)
    if ((a + b) > (n + 1)) {
      return dp(n, n + 1 - b, n + 1 - a)
    }

    const bb = n + 1 - b
    const half = Math.ceil(n / 2)
    let [tmi, tma] = [30, 0]
    if (b > half) {
      const [range1, range2] = [a - 1, bb - a - 1]
      for (let x = 0; x <= range1; x++) {
        for (let y = 0; y <= range2; y++) {
          const z = Math.ceil((b - bb - 1) / 2)
          const [mi, ma] = dp(half, x + 1, x + 1 + y + z + 1)
          tmi = Math.min(mi + 1, tmi)
          tma = Math.max(ma + 1, tma)
        }
      }
    } else {
      const [range1, range2] = [a - 1, b - a - 1]
      for (let x = 0; x <= range1; x++) {
        for (let y = 0; y <= range2; y++) {
          const [mi, ma] = dp(half, x + 1, x + 1 + y + 1)
          tmi = Math.min(mi + 1, tmi)
          tma = Math.max(ma + 1, tma)
        }
      }
    }
    dpMin[n][a][b] = tmi
    dpMax[n][a][b] = tma
    return [dpMin[n][a][b], dpMax[n][a][b]]
  }
};
