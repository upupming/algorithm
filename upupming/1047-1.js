let scanf = require('scanf')

let names = [], res = []

let [n, k] = scanf("%d %d")

for (let i = 0; i < n; i++) {
  let c
  [names[i], c] = scanf("%s %d")
  while (c--) {
    let cNo = scanf("%d")
    // console.log(c, cNo)
    res[cNo] = res[cNo] || new Array()
    res[cNo].push(i)
  }
}

let cmp = (idx1, idx2) => {
  // string 是 immutable 的，copy 会复制大量数据！！！
  // let a = names[idx1]
  // let b = names[idx2]
  if (names[idx1] === names[idx2]) return 0
  else return names[idx1] < names[idx2] ? -1 : 1
}

for (let i = 1; i <= k; i++) {
  console.log(i, res[i].length)
  res[i].sort(cmp)
  for (let j = 0; j < res[i].length; j++) {
    console.log(names[res[i][j]])
  }
}
process.exit(0)

