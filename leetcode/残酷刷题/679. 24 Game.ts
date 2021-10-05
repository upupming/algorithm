function judgePoint24 (cards: number[]): boolean {
  cards.sort((a, b) => a - b)
  do {
    if (canCards24()) return true
  } while (nextPermutation(cards))
  return false

  function reverse<T=number> (arr: T[], begin = 0, end = arr.length): void {
    while (begin < end - 1) {
      swap(arr, begin++, --end)
    }
  }
  function swap<T=number> (arr: T[], l: number, r: number): void {
    const tmp = arr[l]
    arr[l] = arr[r]
    arr[r] = tmp
  }
  function nextPermutation <T=number> (arr: T[]): boolean {
    let i = arr.length - 1
    while (i > 0 && arr[i - 1] >= arr[i]) i--
    if (i <= 0) {
      reverse(arr)
      return false
    }
    let j = i
    while (j + 1 < arr.length && arr[i - 1] < arr[j + 1]) j++
    swap(arr, i - 1, j)
    reverse(arr, i)
    return true
  }
  function canCards24 () {
    const calc = (x: number, y: number) => {
      return new Set([x * y, x / y, x + y, x - y])
    }
    const dp: Array<Array<Set<number>>> = []
    for (let len = 1; len <= 3; len++) {
      for (let i = 0; i + len - 1 < 3; i++) {
        const j = i + len - 1
        dp[i] ??= []; dp[i][j] ??= new Set()
        if (len === 1) dp[i][j] = calc(cards[i], cards[i + 1])
        else {
          for (let k = i; k <= j; k++) {
            const left = k === i ? [cards[k]] : dp[i][k - 1]
            const right = k === j ? [cards[k + 1]] : dp[k + 1][j]
            for (const x of left) {
              for (const y of right) {
                calc(x, y).forEach(dp[i][j].add, dp[i][j])
              }
            }
          }
        }
      }
    }
    return [...dp[0][2]].some(x => Math.abs(x - 24) < 1e-6)
  }
};
