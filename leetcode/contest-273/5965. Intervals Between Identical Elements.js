/**
 * @param {number[]} arr
 * @return {number[]}
 */
 var getDistances = function(arr) {
  // 10^5, 10^5
  // sum[idx][val] += idx
  const n = arr.length
  const ans = Array(n).fill(0)
  // sum[val]
  let sum = Array(1e5+10).fill(0)
  let cnt = Array(1e5+10).fill(0)
  for (let i = 0; i < n; i++) {
      const val = arr[i]
      ans[i] += cnt[val] * i - sum[val]
      sum[val] += i
      cnt[val] += 1
  }
  sum = Array(1e5+10).fill(0)
  cnt = Array(1e5+10).fill(0)
  for (let i = n-1; i >=0; i--) {
      const val = arr[i]
      ans[i] += sum[val] - cnt[val] * i
      sum[val] += i
      cnt[val] += 1
  }
  return ans
};
