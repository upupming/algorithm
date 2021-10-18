function mostCompetitive (nums: number[], k: number): number[] {
  const s: number[] = []
  const n = nums.length
  nums.forEach((x, idx) => {
    while (s.length && x < s[s.length - 1] && (n - idx + s.length - 1 >= k)) {
      s.pop()
    }
    if (s.length < k) s.push(x)
  })
  return s
};
