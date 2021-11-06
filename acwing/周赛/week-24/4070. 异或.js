let input = ''
process.stdin.on('data', (data) => input += data)
process.stdin.on('end', () => {
  const arr = input.replace(/\n/g, ' ').split(' ').filter(s => s !== '').map(Number)
  let max = -1
  for (let i = 1; i < arr.length; i++) {
    max = Math.max(max, arr[i])
  }
  console.log(max ^ arr.pop())
})
