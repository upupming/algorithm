/*
LIS 的 O(n log n) 算法现在基本上已经是必备技能了，必须在 O(1) 时间内想出来，看到群友十几行代码就写出来了，实在是太强了。之前写二分的时候总是感觉很别扭，所以上次比赛的时候用的是树状数组实现的

暴力： dp[i] 表示以 a[i] 为结尾的 LIS 长度，转移过程是 O(n) 的，总时间复杂度 O(n^2)
优化：
使用 q 维护当前的 LIS
但是有一个点需要注意
例如原来是 1 2 9 10，现在来了一个 4，那么可以把当前 LIS 序列变成 1 2 4 10，这样后面如果出现 5 的话可以插到 4 后面了，变成 1 2 4 5，后面出现比 10 小的数也能正确维护了
*/
function lengthOfLIS (nums: number[]): number {
  // 最大值作为哨兵
  const q: number[] = []
  for (const num of nums) {
    // 找到 q 中第 1 个 >= num 的并替换掉，
    // 如果是非递减的 LIS 的话，则是找到第 1 个 > num 的并替换掉
    let [l, r] = [0, q.length]
    while (l < r) {
      const mid = (l + r) >> 1
      // 认为 q.length 处是一个最大值
      if (mid === q.length || q[mid] >= num) r = mid
      else l = mid + 1
    }
    // 没找到
    if (l === q.length) {
      q.push(num)
    } else {
      q[l] = num
    }
  }
  return q.length
};
