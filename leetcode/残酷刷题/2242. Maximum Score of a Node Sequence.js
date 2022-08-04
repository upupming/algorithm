/**
 * @param {number[]} scores
 * @param {number[][]} edges
 * @return {number}
 */
 var maximumScore = function(scores, edges) {
  const n = scores.length
  const e = Array(n).fill(0).map(() => [])
  for (const [x, y] of edges) {
      e[x].push(y)
      e[y].push(x)
  }
  for (const a of e) {
      a.sort((x, y) => scores[y] - scores[x])
  }
  let ans = -1
  for (const [x, y] of edges) {
      for (let a of e[x].slice(0, 3)) {
          for (let b of e[y].slice(0, 3)) {
              if (a!==y&&b!==x&&a!==b) {
                  ans = Math.max(ans, scores[x]+scores[y]+scores[a]+scores[b])
              }
          }
      }
  }
  return ans
};
