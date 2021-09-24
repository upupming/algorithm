/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
const topKFrequent = function (nums, k) {
  const freq = {}
  nums.forEach(x => {
    freq[x] ??= 0
    freq[x]++
  })
  const a = [...new Set(nums)]
  quickSelect(0, a.length - 1, a.length - k)
  return a.slice(a.length - k)
  function quickSelect (l, r, k) {
    if (l >= r) return a[l]
    let [i, j, q] = [l - 1, r + 1, freq[a[l + r >> 1]]]
    while (i < j) {
      do i++; while (freq[a[i]] < q)
      do j--; while (freq[a[j]] > q)
      if (i < j) [a[i], a[j]] = [a[j], a[i]]
    }
    const cnt = j - l + 1
    if (k <= cnt) return quickSelect(l, j, k)
    else quickSelect(j + 1, r, k - cnt)
  }
}
