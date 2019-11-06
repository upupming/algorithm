// var readline = require('readline')
// const r1 = readline.createInterface({
//   input: process.stdin,
//   output: process.stdout
// })
var __readline = require('readline-sync');
__readline.setDefaultOptions({prompt: ''});
var read_line = __readline.prompt;
let tokens, n, k, names = [], res = []
while(line = read_line()){
  // console.log(line)
  global.cnt = global.cnt || 0
  tokens = line.split(' ')
  // console.log(tokens.length)
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
}

main()

var cmp = (idx1, idx2) => {
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

process.exit(0)