/**
 * @param {number} n
 * @param {number[][]} restrictions
 * @param {number[][]} requests
 * @return {boolean[]}
 */
 var friendRequests = function(n, restrictions, requests) {
  /*
  对于 [a, b] 一个 request 来说，如果 (x, y) 存在于 restrictions 里面
  就说明不能够合在一起，x 是 a 代表的集合中的任意元素，y 是 b 代表的集合中的任意元素
  因此 restrictions 也是需要去动态更新的，并查集更新的时候要更新成根节点的限制关系

  0 x 1
  1 - 2
  0 x 2
  */
  const r = [...Array(n)].map(() => [])
  for (const [x, y] of restrictions) {
      r[x][y] = r[y][x] = 1
  }
  const fa = [...Array(n)].map((_, idx) => idx)
  const get = (x) => {
      if (fa[x] === x) return x
      return fa[x] = get(fa[x])
  }
  function merge (x, y) {
    const fx = get(x); const fy = get(y)
    fa[fx] = fy
  }
  const m = requests.length
  const ans = Array(m).fill(false)
  for (let i = 0; i < m; i++) {
      const [a, b] = requests[i]
      if (r[get(a)][get(b)]) ans[i] = false
      else {
          ans[i] = true

          for (let j = 0; j < n; j++) {
              if (r[get(j)][get(a)]) r[get(j)][get(b)] = r[get(b)][get(j)] = true
              if (r[get(j)][get(b)]) r[get(j)][get(a)] = r[get(a)][get(j)] = true
          }

          merge(a, b)
      }
  }
  return ans
};
