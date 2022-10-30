/**
 * @param {string[]} creators
 * @param {string[]} ids
 * @param {number[]} views
 * @return {string[][]}
 */
const mostPopularCreator = function (cs, is, vs) {
  const n = cs.length; const cnt = {}; const by = {}
  for (let i = 0; i < n; i++) {
    if (cnt[cs[i]] == null) cnt[cs[i]] = 0
    if (by[cs[i]] == null) by[cs[i]] = []
    cnt[cs[i]] += vs[i]
    by[cs[i]].push([is[i], vs[i]])
  }
  const hv = Math.max(...Object.values(cnt))
  for (const x of Object.keys(by)) {
    by[x].sort((a, b) => {
      if (a[1] === b[1]) return a[0] < b[0] ? -1 : 1
      return -(a[1] - b[1])
    })
  }
  // console.log(JSON.stringify(by))
  const ans = []; const has = {}
  for (let i = 0; i < n; i++) {
    if (cnt[cs[i]] === hv && !has[cs[i]]) {
      ans.push([cs[i], by[cs[i]][0][0]])
      has[cs[i]] = 1
    }
  }
  return ans
}
