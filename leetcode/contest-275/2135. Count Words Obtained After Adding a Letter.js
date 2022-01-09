/**
 * @param {string[]} startWords
 * @param {string[]} targetWords
 * @return {number}
 ackt
 */
 var wordCount = function(s, t) {
  const sets = [...Array(26)].map(() => new Set())
  for (let i = 0; i < s.length; i++) {
      const str = s[i].split('').sort().join('')
      sets[str.length].add(str)
  }
  let ans = 0
  // console.log(sets)
  for (let i = 0; i < t.length; i++) {
      const str = t[i].split('').sort().join('')
      for (let j = 0; j < str.length; j++) {
          // 去掉 j 处的字符
          let x = str.slice(0, j) + str.slice(j+1)
          if (sets[x.length]?.has(x)) {
              ans++
              break
          }
      }
  }
  return ans
};
