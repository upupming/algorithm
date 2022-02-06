function closestCost (baseCosts: number[], toppingCosts: number[], target: number): number {
  const m = toppingCosts.length
  let ans = 1e10; let cost = 1e10
  for (let i = 0; i < baseCosts.length; i++) {
    const base = baseCosts[i]
    // 三进制，m 位，每一位表示对应的 topping 次数
    for (let j = 0; j < Math.pow(3, m); j++) {
      let tmp = base
      const t = j.toString(3).padStart(m, '0')
      for (let k = 0; k < m; k++) {
        const times = t[k].charCodeAt(0) - '0'.charCodeAt(0)
        tmp += times * toppingCosts[k]
      }

      const newCost = Math.abs(tmp - target)
      if (newCost < cost || (newCost === cost && tmp < ans)) {
        ans = tmp
        cost = newCost
      }
    }
  }
  return ans
};
