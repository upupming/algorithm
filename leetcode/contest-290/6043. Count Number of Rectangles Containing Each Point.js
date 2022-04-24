/**
 * @param {number[][]} rectangles
 * @param {number[][]} points
 * @return {number[]}
 */
const countRectangles = function (rectangles, points) {
  const bh = Array(101).fill(0).map(() => [])
  for (const r of rectangles) {
    const [l, h] = r
    bh[h].push(l)
  }
  bh.forEach(h => h.sort((a, b) => a - b))
  // console.log(bh)
  const ans = []
  for (const [l, h] of points) {
    let cnt = 0
    for (let i = h; i <= 100; i++) {
      let lft = 0; let rgt = bh[i].length
      while (lft < rgt) {
        const mid = lft + rgt >> 1
        if ((mid === bh[i].length) || bh[i][mid] >= l) rgt = mid
        else lft = mid + 1
      }
      cnt += bh[i].length - lft
      // console.log(l, h, i, bh[i], lft)
    }
    ans.push(cnt)
  }
  return ans
}
