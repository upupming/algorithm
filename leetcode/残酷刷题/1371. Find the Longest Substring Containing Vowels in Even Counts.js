/**
 * @param {string} s
 * @return {number}
 */
var findTheLongestSubstring = function(s) {
  // 用 map 记录状态的最早下表
  let st = 0, dict = 'aeiou', mp = {}
  let ans = 0
  // 下标 -1 时状态为 0，边界情况
  mp[0] = -1
  for (let i = 0; i < s.length; i++) {
      let di = dict.indexOf(s[i])
      if (di !== -1) st ^= 1 << di
      if (mp[st] == null) mp[st] = i
      else {
          ans = Math.max(ans, i-mp[st])
      }
  }
  return ans
};
