/**
 * @param {number[][]} pairs
 * @return {number[][]}
 */
const validArrangement = function (pairs) {
  const e = {}; const din = {}; const dout = {}
  for (const [x, y] of pairs) {
    e[x] ??= []
    e[x].push(y)
    dout[x] ??= 0, din[y] ??= 0, din[x] ??= 0, dout[y] ??= 0
    dout[x]++, din[y]++
  }
  let s = pairs[0][0]
  for (const x of Object.keys(dout)) {
    if (dout[x] - din[x] === 1) {
      s = x
      break
    }
  }
  let tmp = []
  const dfs = (x, tmp) => {
    const paths = []
    while (e[x]?.length) {
      const y = e[x].pop()
      dfs(y, tmp)
    }
    tmp.push(x)
  }
  dfs(s, tmp)
  tmp = tmp.reverse()
  const ans = []
  for (let i = 0; i + 1 < tmp.length; i++) {
    ans.push([tmp[i], tmp[i + 1]])
  }
  return ans
}
