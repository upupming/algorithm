const { solve } = require('./合并链表形成环状链表')

let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const data = eval(s[0].replaceAll('{', '[').replaceAll('}', ']'))
  // console.log(data)
  solve(data)
}
/*
{1,5,4,7,3,2,10}


*/
