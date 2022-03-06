function trap (height: number[]): number {
  const s: number[] = []
  let ans = 0
  for (let i = 0; i < height.length; i++) {
    while (s.length && height[s[s.length - 1]] < height[i]) {
      const base = height[s.pop()!]
      if (!s.length) break
      const h = Math.min(height[s[s.length - 1]], height[i]) - base
      const w = i - s[s.length - 1] - 1
      ans += h * w
    }
    s.push(i)
  }
  return ans
};
