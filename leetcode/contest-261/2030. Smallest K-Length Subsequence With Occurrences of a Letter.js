/**
 * @param {string} s
 * @param {number} k
 * @param {character} letter
 * @param {number} repetition
 * @return {string}
 */
const smallestSubsequence = function (s, k, letter, repetition) {
  const ans = []; const n = s.length; let cur = 0
  const cnt = Array(n + 1).fill(0)
  for (let i = n - 1; i >= 0; i--) cnt[i] = cnt[i + 1] + (s[i] === letter)
  for (let i = 0; i < n; i++) {
    // console.log(i, s[i], ans, cur)
    // s[i] 小于单调栈尾，尝试替换掉末尾元素
    while (ans.length && ans[ans.length - 1] > s[i]) {
      if (ans[ans.length - 1] === letter) {
        // 1. 删除一个 letter 之后，后续的剩余的 letter 还能满足 >= repetition 条件
        // 2. 总长度能保证满足 >= k 条件
        // console.log(cur - 1 + cnt[i] >= repetition, ans.length - 1 + n - i >= k)
        if (cur - 1 + cnt[i] >= repetition && ans.length - 1 + n - i >= k) {
          cur--
          ans.pop()
        } else break
      } else {
        // 总长度能保证满足 >= k 条件
        if (ans.length - 1 + n - i >= k) ans.pop()
        else break
      }
    }
    ans.push(s[i])
    cur += (s[i] === letter)
  }
  // console.log(ans, cur)
  while (ans.length > k) {
    if (ans.pop() === letter) cur--
  }
  for (let i = ans.length - 1; i >= 0; i--) {
    if (cur < repetition && ans[i] !== letter) {
      ans[i] = letter
      cur++
    }
  }
  return ans.join('')
}
/*
"hjjhhhmhhwhz"
6
"h"
5
"adffhjfmmmmorsfff"
6
"f"
5
*/
