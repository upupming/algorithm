/**
 * @param {string} s
 * @return {number}
 */
var longestAwesome = function(s) {
  // 状态: 10 个 0 到 10 个 1，表示 0~9 出现次数的奇偶性
  // mp[st] = i 表示状态 st 出现的最早下标
  let mp = {}, n = s.length, st = 0, ans = 1
  mp[0] = -1
  for (let i = 0; i < n; i++) {
      st ^= 1 << (s[i].charCodeAt(0) - '0'.charCodeAt(0))
      // console.log(i, st)
      if (mp[st] == null) mp[st] = i

      // 偶数长度
      ans = Math.max(ans, i-mp[st])
      // 奇数长度
      for (let k = 0; k < 10; k++) {
          let su = st ^ (1 << k)
          if (mp[su] != null)
              ans = Math.max(ans, i-mp[su])
      }
  }
  return ans
};
