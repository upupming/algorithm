const countSmallerBefore = function (nums) {
  const n = nums.length
  const ans = []; const sorted = nums.slice()

  const solve = (i, j) => {
    if (i === j) return ans[i] = 0

    const mid = i + j >> 1
    solve(i, mid)
    solve(mid + 1, j)
    for (let x = mid + 1; x <= j; x++) {
      let l = i; let r = mid
      // 找到 [i, mid] 中最后一个 < nums[x] 的元素
      while (l < r) {
        const m = l + r + 1 >> 1
        if (sorted[m] < nums[x]) l = m
        else r = m - 1
      }
      // 没有小于的
      if (l === i && !(sorted[l] < nums[x])) {}
      //
      else {
        ans[x] += l - i + 1
      }
    }

    // 归并过程
    let x = i; let y = mid + 1
    const tmp = []
    while (x <= mid && y <= j) {
      if (sorted[x] <= sorted[y]) tmp.push(sorted[x++])
      else tmp.push(sorted[y++])
    }
    while (x <= mid) tmp.push(sorted[x++])
    while (y <= j) tmp.push(sorted[y++])

    for (let k = i; k <= j; k++) sorted[k] = tmp[k - i]
  }

  solve(0, n - 1)
  return ans
}
const countLargerAfter = function (nums) {
  const n = nums.length
  const ans = []; const sorted = nums.slice()

  const solve = (i, j) => {
    if (i === j) return ans[i] = 0

    const mid = i + j >> 1
    solve(i, mid)
    solve(mid + 1, j)
    for (let x = i; x <= mid; x++) {
      let l = mid + 1; let r = j
      // 找到 [i, mid] 中第一个 > nums[x] 的元素
      while (l < r) {
        const m = l + r >> 1
        if (sorted[m] > nums[x]) r = m
        else l = m + 1
      }
      // 没有大于的
      if (l === j && !(sorted[l] > nums[x])) {}
      //
      else {
        ans[x] += j - l + 1
      }
    }

    // 归并过程
    let x = i; let y = mid + 1
    const tmp = []
    while (x <= mid && y <= j) {
      if (sorted[x] <= sorted[y]) tmp.push(sorted[x++])
      else tmp.push(sorted[y++])
    }
    while (x <= mid) tmp.push(sorted[x++])
    while (y <= j) tmp.push(sorted[y++])

    for (let k = i; k <= j; k++) sorted[k] = tmp[k - i]
  }

  solve(0, n - 1)
  return ans
}

// 查询前缀和：查询序列 a 第 1~x 个数的和
function ask (c, x) {
  let ans = 0
  for (; x; x -= x & -x) ans += c[x]
  return ans
}
// 单点增加：给序列中的一个数 a[x] 加上 y
// 算法：自下而上每个节点都要增加 y
function add (c, x, y) {
  for (; x < c.length; x += x & -x) c[x] += y
}

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}

0, 1, 2, [3], 2
4, [3], 2, 0, 1

 */
const goodTriplets = function (nums1, nums2) {
  const mp = {}; const n = nums1.length
  for (let i = 0; i < n; i++) mp[nums1[i]] = i
  for (let i = 0; i < n; i++) nums2[i] = mp[nums2[i]]

  // const smallerBefore = countSmallerBefore(nums2); const largerAfter = countLargerAfter(nums2)

  const smallerBefore = []; const largerAfter = []

  const c = Array(n + 1).fill(0)
  for (let i = 0; i < n; i++) {
    // nums2[i] + 1 把从 0 开始的数变成从 1 开始的数
    smallerBefore[i] = ask(c, nums2[i] + 1)
    add(c, nums2[i] + 1, 1)
  }
  c.fill(0)
  for (let i = n - 1; i >= 0; i--) {
    largerAfter[i] = (n - i) - 1 - ask(c, nums2[i] + 1)
    add(c, nums2[i] + 1, 1)
  }

  // console.log(nums2, smallerBefore, largerAfter)
  let ans = 0
  // 枚举 y
  for (let i = 0; i < n; i++) {
    ans += smallerBefore[i] * largerAfter[i]
  }
  return ans
}
