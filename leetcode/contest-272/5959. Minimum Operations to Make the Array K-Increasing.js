/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
const kIncreasing = function (arr, k) {
  const n = arr.length; const ans = n
  let tmp = 0
  for (let i = 0; i < k; i++) {
    const p = []
    for (let j = i, y = 0; j < n; j += k, y++) {
      p.push(arr[j])
    }
    // console.log(p)
    tmp += p.length - lengthOfLIS(p)
  }

  return tmp
}
/*
[12,6,12,6,14,2,13,17,3,8,11,7,4,11,18,8,8,3]
1
*/

function lengthOfLIS (nums) {
  // 最大值作为哨兵
  const q = []
  for (let _i = 0, nums_1 = nums; _i < nums_1.length; _i++) {
    const num = nums_1[_i]
    // 找到 q 中第 1 个 >= num 的并替换掉，
    // 如果是非递减的 LIS 的话，则是找到第 1 个 > num 的并替换掉
    const _a = [0, q.length]; let l = _a[0]; let r = _a[1]
    while (l < r) {
      const mid = (l + r) >> 1
      // 认为 q.length 处是一个最大值
      if (mid === q.length || q[mid] > num) { r = mid } else { l = mid + 1 }
    }
    // 没找到
    if (l === q.length) {
      q.push(num)
    } else {
      q[l] = num
    }
  }
  return q.length
}
