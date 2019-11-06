// 一个答案错误，一个超时
// 看来 node.js 并不适合来读取输入
// 目前没有找到比较好的解决办法
// 多种输入方式都不尽人意

var readline = require('readline')
const r1 = readline.createInterface({
  input: process.stdin,
  output: process.stdout
})

let tokens, n, k, names = [], res = []
r1.on('line', function(line) {
  global.cnt = global.cnt || 0
  tokens = line.split(' ')
  if (global.cnt === 0) {
    [n, k] = [parseInt(tokens[0]), parseInt(tokens[1])]
  } else {
    names.push(tokens[0])
    tokens.slice(2, tokens.length).forEach(val => {
      let cNo = parseInt(val)
      res[cNo] = res[cNo] || new Array()
      res[cNo].push(global.cnt - 1)
    })
  }
  if (++global.cnt === n + 1) main()
})

let cmp = (idx1, idx2) => {
  // string 是 immutable 的，copy 会复制大量数据！！！
  // let a = names[idx1]
  // let b = names[idx2]
  if (names[idx1] === names[idx2]) return 0
  else return names[idx1] < names[idx2] ? -1 : 1
}
function main() {
  for (let i = 1; i <= k; i++) {
    console.log(i, res[i].length)
    res[i].sort(cmp)
    for (let j = 0; j < res[i].length; j++) {
      console.log(names[res[i][j]])
    }
  }
  process.exit(0)
}
