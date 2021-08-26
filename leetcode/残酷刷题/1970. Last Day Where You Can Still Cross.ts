function latestDayToCross (row: number, col: number, cells: number[][]): number {
  const [s, t] = [0, row * col + 1]
  const fa = [...Array<number>(row * col + 2)].map((_, idx) => idx)
  function get (x: number): number {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  function merge (x: number, y: number) {
  // console.log(x, y)
    const fx = get(x); const fy = get(y)
    fa[fx] = fy
  }
  const idx = (r: number, c: number) => (r - 1) * col + c
  for (let j = 1; j <= col; j++) {
    merge(s, idx(1, j))
    merge(t, idx(row, j))
  }
  const f = Array<boolean>(row * col + 2).fill(false)
  const ok = (i: number, j: number) => i >= 1 && i <= row && j >= 1 && j <= col && f[idx(i, j)]
  for (let k = cells.length - 1; k >= 0; k--) {
    // console.log('get', get(s), get(t))
    if (get(s) === get(t)) return k + 1

    const [r, c] = cells[k]
    // console.log('cell', r, c)
    f[idx(r, c)] = true
    if (ok(r - 1, c))
    { merge(idx(r - 1, c), idx(r, c)) }
    if (ok(r + 1, c))
    { merge(idx(r + 1, c), idx(r, c)) }
    if (ok(r, c + 1))
    { merge(idx(r, c + 1), idx(r, c)) }
    if (ok(r, c - 1))
    { merge(idx(r, c - 1), idx(r, c)) }
  }
  return 0
};
