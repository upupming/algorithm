let i = ''
process.stdin.on('data', d => i += d)
process.stdin.on('end', () => {
  const lines = i.split('\n')
  const [n, k] = lines[0].split(' ').map(Number)
  const arr = lines[1].split(' ').map(Number)
  console.log(quickSelect(arr, 0, n - 1, k))
})

function quickSelect (arr, l, r, k) {
  if (l >= r) return arr[l]
  let [i, j, q] = [l - 1, r + 1, arr[l + r >> 1]]
  while (i < j) {
    do i++; while (arr[i] < q)
    do j--; while (arr[j] > q)
    if (i < j) [arr[i], arr[j]] = [arr[j], arr[i]]
  }
  const cnt = j - l + 1
  if (cnt >= k) return quickSelect(arr, l, j, k)
  else return quickSelect(arr, j + 1, r, k - cnt)
}
