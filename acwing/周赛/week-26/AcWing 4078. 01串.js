function select (n, k) {
  let ans = 0
  for (let i = 0; i < 1 << n; i++) {
    let isSuit = true
    for (let j = 0; j < n; j++) {
      // 后面 k 位必须都是 1
      if (i >> j & 1) {
        let bits = 0
        for (let l = j; l <= j + k - 1; l++) {
          if ((i >> l & 1)) bits++
        }
        if (bits !== k) {
          isSuit = false
          break
        }
        j = j + k - 1
      }
    }
    ans += isSuit
  }

  return ans
}

const cache = []
const P = 1e9 + 7

function select_optimized (n, k) {
  if (cache[n] == undefined)cache[n] = []
  if (cache[n][k] !== undefined) return cache[n][k]

  let ans = 0

  if (n < k) ans = 1
  else if (n === k) ans = 2
  else {
    ans = (select_optimized(n - 1, k) + select_optimized(n - k, k)) % P
  }

  return cache[n][k] = ans
}

const pre = [0]

let input = ''
process.stdin.on('data', (data) => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t, k] = lines[0].split(' ').map(Number)
  for (let i = 1; i <= 1e5 + 10; i++) {
    pre[i] = (pre[i - 1] + select_optimized(i, k)) % P
  }
  for (let i = 1; i <= t; i++) {
    const [l, r] = lines[i].split(' ').map(Number)
    console.log((pre[r] - pre[l - 1] + P) % P)
  }
})

/*
for (let i = 1; i <= 10; i++) {
  console.log(i, 2, select(i, 2))
  console.assert(select(i, 2) === select_optimized(i, 2))
}
console.log()
for (let i = 1; i <= 10; i++) {
  console.log(i, 3, select(i, 3))
  console.assert(select(i, 3) === select_optimized(i, 3))
}
console.log()
for (let i = 1; i <= 10; i++) {
  console.log(i, 4, select(i, 4))
  console.assert(select(i, 4) === select_optimized(i, 4))
}
*/
