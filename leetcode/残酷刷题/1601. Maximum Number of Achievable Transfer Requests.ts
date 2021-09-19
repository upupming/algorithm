function maximumRequests (n: number, requests: number[][]): number {
  let ans = 0
  const cntBits = (x: number) => {
    let ans = 0
    while (x) {
      ans += x & 1
      x >>= 1
    }
    return ans
  }
  for (let i = 0; i < 1 << n; i++) {
    if (ok(i)) ans = Math.max(ans, cntBits(i))
  }
  return ans
  function ok (i: number) {
    const deg: number[] = []
    for (let k = 0; k < n; k++) {
      if (i >> k & 1) {
        deg[requests[k][0]] ??= 0; deg[requests[k][0]]++
        deg[requests[k][1]] ??= 0; deg[requests[k][1]]--
      }
    }
    return !deg.some(x => x !== 0)
  }
};
