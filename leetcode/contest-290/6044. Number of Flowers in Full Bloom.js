/**
 * @param {number[][]} flowers
 * @param {number[]} persons
 * @return {number[]}
 */
const fullBloomFlowers = function (flowers, persons) {
  // 离散化，注意右端点的值是 e+1
  const p = []
  for (const [s, e] of flowers) p.push(s, e + 1)
  p.sort((a, b) => a - b)
  const mp = {}
  for (let i = 0; i < p.length; i++) mp[p[i]] = i

  // 计算差分数组
  const diff = Array(p.length).fill(0)
  for (const [s, e] of flowers) {
    const si = mp[s]; const ei = mp[e + 1]
    diff[si] += 1
    diff[ei] -= 1
  }

  // 利用差分数组计算原始数组，表示每个时间点的花的数量
  const a = []; let prev = 0
  const pi = persons.map((p, i) => [p, i]).sort((a, b) => a[0] - b[0])
  let j = 0; const ans = []
  for (let i = 0; i < diff.length; i++) {
    while (j < pi.length && pi[j][0] < p[i]) {
      ans[pi[j][1]] = prev, j++
    }
    a[i] = prev + diff[i]
    prev = a[i]
  }
  while (j < pi.length) ans[pi[j][1]] = prev, j++
  return ans
}
/*
[[19,37],[19,38],[19,35]]
[6,7,21,1,13,37,5,37,46,43]

[0,0,3,0,0,2,0,2,0,0]

[[11,11],[24,46],[3,25],[44,46]]
[1,8,26,7,43,26,1]

[0,1,1,1,1,1,0]
*/
