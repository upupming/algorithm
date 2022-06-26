/**
 * @param {number[][]} grid
 * @return {boolean}
 */
 var checkXMatrix = function(g) {
  const n = g.length
  let ok = true
  for (let i = 0; i < n; i++) {
      for (let j = 0; j < n; j++) {
          if (i === j || (i+j) === n-1) {
              if (g[i][j] === 0) ok = false
          } else {
              if (g[i][j] !== 0) ok = false
          }
      }
  }
  return ok
};
