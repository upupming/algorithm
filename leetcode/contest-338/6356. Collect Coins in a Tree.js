/**
 * @param {number[]} coins
 * @param {number[][]} edges
 * @return {number}
 */
const collectTheCoins = function (c, eg) {
  const n = c.length
  const deg = Array(c.length).fill(0)
  const e = Array(n).fill(0).map(() => new Set())
  for (const [a, b] of eg) {
    e[a].add(b)
    e[b].add(a)
    deg[a]++
    deg[b]++
  }
  const q = []; const del = new Set()
  for (let i = 0; i < n; i++) {
    if (deg[i] === 1 && !c[i]) q.push(i)
  }
  // console.log(q, deg[6], c[6])
  while (q.length) {
    const x = q.shift()
    del.add(x)
    for (const y of e[x]) {
      e[y].delete(x)
      if (--deg[y] === 1 && !c[y]) q.push(y)
    }
  }
  // console.log(del)

  let x
  for (let i = 0; i < n; i++) {
    if (!del.has(i)) {
      x = i
      break
    }
  }
  // 全都删除了
  if (x == null) return 0

  const q1 = []; const time = []
  for (let i = 0; i < n; i++) {
    if (c[i] && deg[i] === 1) q1.push(i), time[i] = 0
  }
  while (q1.length) {
    const x = q1.shift()
    for (const y of e[x]) {
      // if (time[y] == null) {
      // console.log(x, y)

      if (--deg[y] === 1) {
        time[y] = time[x] + 1
        q1.push(y)
      }
      // }
    }
  }

  // console.log(time)
  let ans = 0
  for (const [a, b] of eg) {
    if (del.has(a) || del.has(b)) continue
    if (time[a] >= 2 && time[b] >= 2) ans += 2
  }
  return ans
}

// console.log(collectTheCoins([1, 0, 0, 0, 0, 1],
//   [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5]]))
// console.log(collectTheCoins([0, 0, 0, 1, 1, 0, 0, 1],
//   [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [5, 6], [5, 7]]))
// console.log(collectTheCoins([1],
//   []))
// console.log(collectTheCoins([0, 0],
//   [[0, 1]]))
// console.log(collectTheCoins(
//   [1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1],
//   [[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [4, 6], [5, 7], [6, 8], [7, 9], [9, 10], [8, 11], [11, 12], [12, 13], [11, 14], [12, 15], [12, 16], [13, 17], [17, 18]]
// ))
