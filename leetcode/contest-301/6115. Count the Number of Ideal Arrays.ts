function idealArrays (n: number, maxValue: number): number {
  // f[i][j] 表示 arr[i] 与 arr[i - 1] 不能相等 的情况下，以 i 为最后一个元素，长度为 j 的方案数
  // 因为 maxValue <= 1e4, j <= log_2 maxValue <= 13.2 < 14
  const MAX_LEN = 14; const P = 1e9 + 7

  // maxValue log maxValue 时间复杂度求因子
  const frac = Array(maxValue + 1).fill(0).map<number[]>(() => [])
  for (let i = 1; i <= maxValue; i++) {
    for (let j = 2 * i; j <= maxValue; j += i) {
      if (j % i === 0) frac[j].push(i)
    }
  }

  // maxValue log maxValue log maxValue
  const f = Array(maxValue + 1).fill(0).map(() => Array<number>(MAX_LEN + 1).fill(0))
  for (let i = 1; i <= maxValue; i++) {
    f[i][1] = 1
    for (let j = 2; j <= MAX_LEN; j++) {
      for (const k of frac[i]) f[i][j] = (f[i][j] + f[k][j - 1]) % P
    }
  }

  // n log maxValue
  const c = Array(n + 1).fill(0).map(() => Array<number>(MAX_LEN + 1).fill(0))
  c[0][0] = 1
  for (let i = 1; i <= n; i++) {
    c[i][0] = 1
    for (let j = 1; j <= MAX_LEN && j <= i; j++) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P
    }
  }

  // maxValue log maxValue
  let ans = 0
  // 真正的长度为 n，arr[i] 与 arr[i - 1] 不能相等的情况下的长度为 t，在 n-1 个位置选 t-1 个位置作为值改变的起始点
  for (let i = 1; i <= maxValue; i++) {
    for (let j = 1; j <= MAX_LEN; j++) {
      ans = (ans + Number(BigInt(c[n - 1][j - 1]) * BigInt(f[i][j]) % BigInt(P))) % P
    }
  }
  return ans
};

export declare const a: 1
