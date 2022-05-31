/**
 * @param {number[]} arr
 * @return {number}
 */
const sumSubarrayMins = function (arr) {
  const n = arr.length
  arr[-1] = arr[n] = -1
  let s = [-1]; const l = []; const r = []; let ans = 0
  for (let i = 0; i < n; i++) {
    while (arr[s[s.length - 1]] >= arr[i]) s.pop()
    l[i] = s[s.length - 1]
    s.push(i)
  }
  s = [n]
  for (let i = n - 1; i >= 0; i--) {
    while (arr[s[s.length - 1]] > arr[i]) s.pop()
    r[i] = s[s.length - 1]
    s.push(i)

    ans = (ans + arr[i] * (i - l[i]) * (r[i] - i)) % (1e9 + 7)
  }
  return ans
}
