function findAllPeople(n: number, meetings: number[][], firstPerson: number): number[] {
  const fa = [...Array(n)].map((_, idx) => idx)
  const get = (x: number): number => {
    if (x === fa[x]) return x
    return fa[x] = get(fa[x])
  }
  const merge = (x: number, y: number) => {
    let fx = get(x); let fy = get(y)
    // 优先让 0 做根节点
    if (fx === 0) [fx, fy] = [fy, fx]
    fa[fx] = fy
  }
  meetings.sort((a, b) => a[2] - b[2])
  const m = meetings.length
  merge(0, firstPerson)
  for (let i = 0; i < m; ) {
    let time = meetings[i][2]
    let j = i
    while (j < m && meetings[j][2] === time) {
      merge(meetings[j][0], meetings[j][1])
      j++
    }
    for (let k = i; k < j; k++) {
      const [a, b] = meetings[k]
      if (get(a) !== 0) fa[a] = a
      if (get(b) !== 0) fa[b] = b
    }
    i = j
  }
  const ans = [0]
  for (let i = 1; i < n; i++) {
    if (get(i) === get(0)) ans.push(i)
  }
  return ans
};
