/**
 * @param {string} expression
 * @return {string}
 */
 var minimizeResult = function(e) {
  const idx = e.indexOf('+')
  const d = String(e).split('')
  let ans = 1e10, exp
  for (let l = 0; l < idx; l++) {
      for (let r = idx+2; r < e.length+1; r++) {
          let e1 = e.slice(0, l)
          let e2 = e.slice(l, r)
          let e3 = e.slice(r)
          let ex = `(${e2})`
          if (e1.length) ex = e1 + '*' + ex
          if (e3.length) ex = ex + '*' + e3
          let x = eval(ex)
          if (x < ans) {
              ans = x
              exp = ex.split('').filter(x => x !== '*').join('')
          }
          // console.log(l, r, e1, e2, e3, ex, eval(ex))
      }
  }
  return exp
};
