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
function quickSort1 (l, r) {
  if (l >= r) return
  // 注意 q 除了 arr[l] 以外的数都可以赋值，不然会出现无限递归，防止被卡去中间值作为基准, l+r>>1 有可能求出 l 来，因此用 l+r+1>>1
  let [i, j, q] = [l - 1, r + 1, arr[l + r + 1 >> 1]]
  while (i < j) {
    do i++; while (arr[i] < q)
    do j--; while (arr[j] > q)
    if (i < j) [arr[i], arr[j]] = [arr[j], arr[i]]
  }
  quickSort(l, i - 1)
  quickSort(i, r)
}

// 暴力解法，需要额外的空间开销
function quickSelectNaive (l, r) {
  if (l >= r) return arr[l]
  const q = arr[l + r >> 1]

  const a = []; const b = []; const c = []
  for (let p = l; p <= r; p++) {
    if (arr[p] === q) c.push(arr[p])
    else if (arr[p] < q) a.push(arr[p])
    else b.push(arr[p])
  }
  const d = [...a, ...c, ...b]
  for (let p = l; p <= r; p++) {
    arr[p] = d[p - l]
  }

  // console.log(a, b, c, l, r, q)
  // 不能让左右两边的数组任何一个数组为空，否则会死循环
  const h1 = a.length + (a.length === 0 ? Math.ceil(c.length / 2) : Math.floor(c.length / 2))
  quickSelectNaive(l, l + h1 - 1)
  quickSelectNaive(l + h1, r)
}
