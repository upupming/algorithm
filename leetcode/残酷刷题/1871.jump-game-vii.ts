/*
 * @lc app=leetcode id=1871 lang=typescript
 *
 * [1871] Jump Game VII
 * 可以用前缀和或者单调队列解决
 * 前缀和：f[i] 表示 i 是否可达，g[i] 为 f[1~i] 的前缀和，计算 f[i] 的时候，需要保证 f[i-maxJump~i-minJump] 之间必须有 1，等价于区间和 >= 1
 * 单调队列: 维护一个 maxJump - minJump 的可达的区间，每次加入新元素的时候，删去距离较远的元素即可
 */

// @lc code=start
function canReach (s: string, minJump: number, maxJump: number): boolean {
  function canReachPreSum (s: string, minJump: number, maxJump: number): boolean {
    const n = s.length
    const [f, g] = [Array<number>(n + 1).fill(0), Array<number>(n + 1).fill(0)]
    s = ' ' + s
    f[1] = g[1] = 1
    for (let i = 2; i <= n; i++) {
      const [left, right] = [Math.max(i - maxJump, 1), i - minJump]
      if (right >= 1 && s[i] === '0' && g[right] - g[left - 1]) {
        f[i] = 1
      } else {
        f[i] = 0
      }
      g[i] = g[i - 1] + f[i]
    }
    return Boolean(f[n])
  }

  function canReachMonotonicQueue (s: string, minJump: number, maxJump: number): boolean {
    const [q, n] = [Array<number>(), s.length]
    q.push(0)
    for (let i = 1; i < n; i++) {
      // 删除较远的队头
      while (i - q[0] > maxJump) q.shift()
      if (s[i] === '0' && i - q[0] >= minJump) q.push(i)
    }
    return q[q.length - 1] === n - 1
  }

  return canReachMonotonicQueue(s, minJump, maxJump)
};
// @lc code=end
