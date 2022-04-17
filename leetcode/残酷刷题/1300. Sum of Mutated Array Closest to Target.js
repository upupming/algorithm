/**
 * @param {number[]} arr
 * @param {number} target
 * @return {number}
 */
const findBestValue = function (arr, target) {
  arr.sort((a, b) => a - b)
  const n = arr.length
  const sum = []
  sum[-1] = 0
  for (let i = 0; i < n; i++) sum[i] = sum[i - 1] + arr[i]
  const get = (x) => {
    // <=x 的最后的位置
    let l = -1; let r = n - 1
    while (l < r) {
      const mid = l + r + 1 >> 1
      if (arr[mid] > x) r = mid - 1
      else l = mid
    }
    // [0, l] 不变 [l+1, ) 变成 x
    return sum[l] + (n - l - 1) * x
  }
  let l = 0; let r = 1e5
  while (l < r) {
    const mid = l + r >> 1
    if (get(mid) >= target) r = mid
    else l = mid + 1
  }
  // 永远小于 target
  if (get(l) < target) return arr[arr.length - 1]
  else {
    const ans1 = Math.abs(get(l) - target)
    const ans2 = Math.abs(get(l - 1) - target)
    if (ans1 < ans2) return l
    else return l - 1
  }
}
