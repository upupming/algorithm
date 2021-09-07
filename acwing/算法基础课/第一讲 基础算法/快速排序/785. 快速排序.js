const input = []
process.stdin.on('data', data => input.push(data))
let arr
process.stdin.on('end', () => {
  const lines = input.join('').split('\n')
  const n = Number(lines[0])
  arr = lines[1].split(' ').filter(s => s !== '').map(Number)
  quickSort(0, n - 1)
  console.log(arr.join(' '))
})
function quickSort (l, r) {
  if (l >= r) return
  // 注意 q 除了 arr[r] 以外的数都可以赋值，不然会出现无限递归，防止被卡去中间值作为基准
  let [i, j, q] = [l - 1, r + 1, arr[l + r >> 1]]
  while (i < j) {
    do i++; while (arr[i] < q)
    do j--; while (arr[j] > q)
    if (i < j) [arr[i], arr[j]] = [arr[j], arr[i]]
  }
  quickSort(l, j)
  quickSort(j + 1, r)
}
