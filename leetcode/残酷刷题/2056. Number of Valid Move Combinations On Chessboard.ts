function countCombinations (pieces: string[], positions: number[][]): number {
  const combinations = new Set<string>()
  const horizontal = [[1, 0], [-1, 0]]
  const vertical = [[0, 1], [0, -1]]
  const diagonal = [[1, 1], [-1, -1], [1, -1], [-1, 1]]
  const rules: Record<string, number[][]> = {
    rook: [...horizontal, ...vertical],
    queen: [...horizontal, ...vertical, ...diagonal],
    bishop: [...diagonal]
  }
  const n = pieces.length
  const pieceRules = pieces.map(p => rules[p])
  // n 个棋子，每个棋子选择一个方向，所有可能的选择方案
  const directions: number[][][] = []
  const dfs = (i: number, d: number[][]) => {
    if (i === n) {
      directions.push(d)
      return
    }
    for (let j = 0; j < pieceRules[i].length; j++) {
      // 第 i 个棋子选择第 j 个走法
      d.push(pieceRules[i][j])
      // 这里的 slice() 浅拷贝很重要，不然的话虽然在 dfs 叶子节点 directions.push 了 d，但是我们后面又 d.pop() 了，导致 directions 里面全是空数组
      dfs(i + 1, d.slice())
      d.pop()
    }
  }
  dfs(0, [])

  interface IState {
    positions: number[][]
    running: number
  }
  const hashPositions = (positions: number[][]) => positions.reduce((p, c) => p + '_' + c[0].toString() + c[1].toString(), '')
  const hash = ({ positions, running }: IState) => hashPositions(positions) + '_' + running.toString()
  const equal = ([a, b]: number[], [i, j]: number[]) => a === i && b === j
  const valid = ([i, j]: number[]) => i >= 1 && i <= 8 && j >= 1 && j <= 8
  for (let i = 0; i < directions.length; i++) {
    const d = directions[i]
    // 初始状态
    const q = [{
      positions,
      // 刚开始的时候 n 个棋子都在走
      running: (1 << n) - 1
    }]
    const v = new Set<string>()
    while (q.length) {
      const {
        positions,
        running
      } = q.shift()!
      combinations.add(hashPositions(positions))

      const addNewStateIfNotExist = (newState: IState) => {
        const h = hash(newState)
        if (newState.positions.length === n && !v.has(h)) {
          q.push(newState)
          v.add(h)
        }
      }

      // 尝试减少正在移动的棋子个数
      for (let k = running; k > 0; k = (k - 1) & running) {
        addNewStateIfNotExist({
          positions,
          running: k
        })
      }

      const newPositions: number[][] = []
      let ok = true
      // 所有棋子全部走动 1 格
      for (let j = 0; j < n; j++) {
        const cur = positions[j].slice()
        if (running >> j & 1) {
          cur[0] += d[j][0]; cur[1] += d[j][1]
          // console.log(j, running, running >> j & 1, d, cur)
        }
        // 如果出界了，就不合法
        if (!valid(cur)) break
        // 如果出现冲突，就不合法
        for (let k = 0; k < j; k++) {
          if (equal(cur, newPositions[k])) {
            ok = false
            break
          }
        }
        if (!ok) break
        newPositions.push(cur)
      }
      if (ok) {
        // console.log(newPositions, 'from', positions, running)
        addNewStateIfNotExist({
          positions: newPositions,
          running
        })
      }
    }
  }
  return combinations.size
};
