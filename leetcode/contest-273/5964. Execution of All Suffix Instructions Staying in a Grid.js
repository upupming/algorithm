/**
 * @param {number} n
 * @param {number[]} startPos
 * @param {string} s
 * @return {number[]}
 */
 var executeInstructions = function(n, startPos, s) {
  const m = s.length
  const ans = []
  const mp = {
      'L': [0, -1],
      'R': [0, 1],
      'U': [-1, 0],
      'D': [1, 0],
  }
  const valid = ([x, y]) => {
      return x >= 0 && x < n && y >=0 && y < n
  }
  for (let i = 0; i < m; i++) {
      let step = 0, pos = startPos
      for (let j = i; j < m; j++, step++) {
          // console.log(i, j, pos)
          pos = [pos[0] + mp[s[j]][0], pos[1] + mp[s[j]][1]]
          if (!valid(pos)) break
      }
      ans.push(step)
  }
  return ans
};
