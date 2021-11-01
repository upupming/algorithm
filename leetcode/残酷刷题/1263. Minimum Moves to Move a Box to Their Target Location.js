/**
 * @param {character[][]} grid
 * @return {number}
 */
const minPushBox = function (grid) {
  // [bx, by, sx, sy] 表示一个状态
  // 需要使用 deque 来进行 BFS，因为边权可能为 0 和 1，0 放队首、1 放队尾
  const m = grid.length; const n = grid[0].length
  let b, s, t
  for (let i = 0; i < m; i++) {
    for (let j = 0; j < n; j++) {
      if (grid[i][j] === 'B') b = [i, j]
      else if (grid[i][j] === 'S') s = [i, j]
      else if (grid[i][j] === 'T') t = [i, j]
    }
  }
  const q = []; const d = []
  const set = (bx, by, sx, sy, val) => {
    d[bx] ??= [], d[bx][by] ??= [], d[bx][by][sx] ??= [], d[bx][by][sx][sy] = val
  }
  const get = (bx, by, sx, sy, val) => d?.[bx]?.[by]?.[sx]?.[sy] ?? -1
  const dx = [0, 0, 1, -1]; const dy = [1, -1, 0, 0]
  const valid = (i, j) => i >= 0 && i < m && j >= 0 && j < n && grid[i][j] != '#'
  q.push([...b, ...s, 0])
  while (q.length) {
    const [bx, by, sx, sy, d] = q.shift()
    // 已经访问过的状态，无需拓展
    if (get(bx, by, sx, sy) !== -1) continue
    set(bx, by, sx, sy, d)
    if (bx === t[0] && by === t[1]) return d
    // 只有 player 往上下左右走
    for (let i = 0; i < 4; i++) {
      const sx1 = sx + dx[i]; const sy1 = sy + dy[i]
      if (valid(sx1, sy1) && !(sx1 === bx && sy1 === by)) {
        // 不需要代价，边权为 0，因此放入队首
        q.unshift([bx, by, sx1, sy1, d])
      }
    }
    // player 推着箱子走
    for (let i = 0; i < 4; i++) {
      if (sx + dx[i] === bx && sy + dy[i] === by) {
        const sx1 = bx; const sy1 = by
        const bx1 = bx + dx[i]; const by1 = by + dy[i]
        if (valid(bx1, by1)) {
          q.push([bx1, by1, sx1, sy1, d + 1])
        }
      }
    }
  }
  return -1
}
