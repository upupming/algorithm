let input = ''
process.stdin.on('data', data => input += data)
process.stdin.on('end', () => {
  const lines = input.split('\n')
  const [t] = lines[0].split(' ').map(Number)
  for (let i = 1, kase = 1; kase <= t; kase++) {
    const [k] = lines[i].split(' ').map(Number)
    const x = [[]]; const y = [[]]
    const xs = new Set(); const ys = new Set()
    const xsum = [[0, 0]]; const ysum = [[0, 0]]
    for (let l = 1; l <= k; l++) {
      const [x1, y1, x2, y2] = lines[i + l].split(' ').map(Number)
      x.push([x1, x2]); y.push([y1, y2])
      xs.add(x1), xs.add(x2); ys.add(y1), ys.add(y2)
    }

    const solve1 = () => {
      const xb = [...xs].sort((a, b) => a - b)
      // 第一次 WA 主要是没有考虑到需要将盒子按照左边界、右边界分别排序
      // 排序之后的处理很容易出错，下标考虑极其复杂，我做完之后感觉其实建议重新建立新数组，而不是在下标数组上进行排序
      const s1 = [...Array(k)].map((_, idx) => idx + 1).sort((i, j) => x[i][0] - x[j][0])
      const s2 = [...Array(k)].map((_, idx) => idx + 1).sort((i, j) => x[i][1] - x[j][1])
      for (let i = 1; i <= k; i++) {
        xsum.push([
          xsum[i - 1][0] + x[s1[i - 1]][0],
          xsum[i - 1][1] + x[s2[i - 1]][1]
        ])
      }

      let minCost = Infinity; let bestX = -1
      for (let i = 0, l = 0, r = 0; i < xb.length; i++) {
        const curX = xb[i]
        // 保证 0~l-1 里面右侧边不到 curX
        while (l < k && x[s2[l]][1] < curX) l++
        // 保证 r~k-1 里面左侧边不到 curX
        while (r < k && x[s1[r]][0] <= curX) r++
        // 0~l-1 共 l 个元素，所以是 curX * l，排序之后从 0~l-1 的元素在 xsum 里面的下标其实是 1~l 所以是 xsum[l]
        const left = (l < k) ? (curX * l - xsum[l][1]) : 0
        // r~k-1 共 k-r 个元素，所以是 curX * (k - r)，排序之后从 r~k-1 的元素在 xsum 里面的下标其实是 r+1~k 所以是 xsum[k] - xsum[r]
        const right = (r < k) ? ((xsum[k][0] - xsum[r][0]) - curX * (k - r)) : 0
        const cost = left + right
        // console.log(i, curX, l, r, left, right, cost)
        if (cost < minCost) {
          minCost = cost
          bestX = curX
        }
      }
      return bestX
    }
    const solve2 = () => {
      const yb = [...ys].sort((a, b) => a - b)
      const s1 = [...Array(k)].map((_, idx) => idx + 1).sort((i, j) => y[i][0] - y[j][0])
      const s2 = [...Array(k)].map((_, idx) => idx + 1).sort((i, j) => y[i][1] - y[j][1])
      for (let i = 1; i <= k; i++) {
        ysum.push([
          ysum[i - 1][0] + y[s1[i - 1]][0],
          ysum[i - 1][1] + y[s2[i - 1]][1]
        ])
      }

      let minCost = Infinity; let bestY = -1
      for (let i = 0, l = 0, r = 0; i < yb.length; i++) {
        const curY = yb[i]
        while (l < k && y[s2[l]][1] < curY) l++
        while (r < k && y[s1[r]][0] <= curY) r++
        const left = (l < k) ? (curY * l - ysum[l][1]) : 0
        const right = (r < k) ? ((ysum[k][0] - ysum[r - 1 + 1][0]) - curY * (k - r)) : 0
        const cost = left + right
        if (cost < minCost) {
          minCost = cost
          bestY = curY
        }
      }
      return bestY
    }

    console.log(`Case #${kase}: ${solve1()} ${solve2()}`)

    i += k + 1
  }
})
