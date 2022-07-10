/**
 * @param {number[]} amount
 * @return {number}
 */
 var fillCups = function(a) {
  a = a.sort((x, y) => x-y).filter(x => x!= 0)
  let ans = 0
  while (a.length) {
      // console.log(a)
      if (a.length >= 2) a[0]--, a[a.length-1]--
      else a[0]--
      a = a.sort((x, y) => x-y).filter(x => x!= 0)
      ans++
  }
  return ans
};
