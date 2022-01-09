/**
 * @param {number[]} plantTime
 * @param {number[]} growTime
 * @return {number}
 */
 var earliestFullBloom = function(plantTime, growTime) {
  const n = plantTime.length
  const idx = [...Array(n)].map((_, idx) => idx).sort((i, j) => -(growTime[i] - growTime[j]))
  let ans = 0, day = 0
  for (const i of idx) {
      const [p, g] = [plantTime[i], growTime[i]]
      day += p
      ans = Math.max(day + g, ans)
  }
  return ans
};
