/**
 * @param {number[]} pref
 * @return {number[]}
 */
 var findArray = function(pref) {
  let ans = [pref[0]], t = pref[0]
  for (let i = 1; i < pref.length; i++) {
      ans.push(t^pref[i])
      t ^= t^pref[i]
  }
  return ans
};
