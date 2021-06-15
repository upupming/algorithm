/*
平时很少遇到二分判定的时候是 O(n) 的算法，这个就是，有点难想
二分移除的个数 k，判定移除之后的字符串是不是 s 的子序列，判定算法是 O(n) 的双指针算法，可以先写不需要删除的情况，再考虑需要删除的情况，发现用一个 map 对元素映射到其下标就可以了，如果下标小于当前二分长度，说明已经被删除了（题目有个关键条件 removable 的元素是不同的）
*/
function maximumRemovals (s: string, p: string, removable: number[]): number {
  const [n, m, t] = [s.length, p.length, removable.length]
  let [l, r] = [0, t]
  const r2Idx = new Map()
  for (let i = 0; i < t; i++) {
    r2Idx.set(removable[i], i)
  }
  while (l < r) {
    const mid = (l + r + 1) >> 1
    if (valid(mid)) {
      l = mid
    } else {
      r = mid - 1
    }
  }
  return l
  function valid (mid: number) {
    let [i, j] = [0, 0]
    for (; i < n && j < m; i++) {
      if (r2Idx.has(i) && r2Idx.get(i) < mid) continue
      if (s[i] === p[j]) j++
    }
    return j === m
  }
};
