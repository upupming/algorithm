/*
由于只有 10 个不同的字母，状态只有奇数偶数次两种，使用二进制的 0/1 位表示字母出现的次数的奇偶性，初始为 0，每增加一个就异或一下 1
前缀和，sum[i][k] 表示 1~i 的状态 k 出现总次数，对于以第 i 个下标为结尾，求所有可能的下标 j (j<=i) 满足 k' 和 k 最多只有 1 位不同（也就是最多只有 1 位是出现奇数次）
因为每次只需要求 sum[i][k'] - sum[0][k']，可以滚动更新删去第 1 维
*/
function wonderfulSubstrings (word: string): number {
  const sum = new Array<number>(1 << 10).fill(0)
  sum[0] += 1
  let k = 0
  let ans = 0
  for (let i = 0; i < word.length; i++) {
    k = k ^ (1 << (word.charCodeAt(i) - 'a'.charCodeAt(0)))
    ans += sum[k]
    for (let j = 0; j < 10; j++) {
      ans += sum[k ^ (1 << j)]
    }

    sum[k] += 1
  }
  return ans
};
