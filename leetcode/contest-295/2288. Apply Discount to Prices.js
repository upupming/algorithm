/**
 * @param {string} sentence
 * @param {number} discount
 * @return {string}
 */
const discountPrices = function (s, d) {
  return s.split(' ').map(x => {
    // console.log(x)
    if (x[0] === '$' && x.length > 1) {
      let ok = true
      for (let i = 1; i < x.length; i++) {
        // console.log(x[i], x.charCodeAt(i), '0'.charCodeAt(i), '9'.charCodeAt(i))
        if ((x.charCodeAt(i) < '0'.charCodeAt(0)) || (x.charCodeAt(i) > '9'.charCodeAt(0))) {
          ok = false
          break
        }
      }
      // console.log(x, ok)
      if (ok) {
        return '$' + (parseFloat(x.slice(1)) * (100 - d) / 100).toFixed(2)
      }
    }
    return x
  }).join(' ')
}
