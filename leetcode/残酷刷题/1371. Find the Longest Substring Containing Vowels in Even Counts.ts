/*
sum[k][j] 表示字母 k 的从 1~j 的异或前缀和
对于每个 i ，要找最前面的 j 满足 5 个元音字母的 [i, j] 出现次数都是偶数次
同样可以用 map 存储所有字母的奇偶情况的最小下标
*/
function findTheLongestSubstring (s: string): number {
  const idx: number[] = []
  idx[0] = -1
  const v = 'aeiou'
  let [f, ans] = [0, 0]
  for (let i = 0; i < s.length; i++) {
    const k = v.indexOf(s[i])
    if (k !== -1) {
      f ^= (1 << k)
    }
    // 找最小的 j 满足 [j, i] 区间都是偶数次
    if (idx[f] !== undefined) {
      ans = Math.max(ans, i - idx[f])
    }
    idx[f] ??= i
  }
  return ans
};
