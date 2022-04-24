
function ListNode (x) {
  this.val = x
  this.next = null
}

/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * @param a ListNode类一维数组 指向每段碎片的开头
 * @return ListNode类
 */
function solve (input) {
  const a = input
  const a = []
  for (const p of input) {
    const t = []
    let cur = p
    while (cur) {
      t.push(cur.val)
      cur = cur.next
    }
    a.push(t)
  }
  // map from val to node
  // val: [i, j]
  const map = {}
  const s = new Set()
  for (let i = 0; i < a.length; i++) {
    const arr = a[i]
    const n = arr.length
    // 首部和原来的相交
    if (map[arr[0]] != null) {
      const [x, y] = map[arr[0]]
      // 把当前的数移过去
      for (let k = 0; k < arr.length; k++) {
        a[x][y + k] = arr[k]
        map[arr[k]] = [x, y + k]
      }
    }
    // 尾部和原来的相交
    else if (map[arr[n - 1]] != null) {
      const [x, y] = map[arr[n - 1]]
      for (let k = 0; k < n; k++) {
        map[arr[k]] = [i, k]
      }
      // 把 a[x] 移过来
      for (let k = 0; k < a[x].length; k++) {
        arr[n + k] = a[x][y + k]
        map[arr[n + k]] = [i, n + k]
      }
      s.delete(x)
      s.add(i)
    } else {
      for (let k = 0; k < n; k++) {
        map[arr[k]] = [i, k]
      }
      s.add(i)
    }
  }
  function less (arrA, arrB) {
    for (let i = 0; i < Math.min(arrA.length, arrB.length); i++) {
      if (arrA[i] < arrB[i]) {
        return -1
      } else if (arrA[i] > arrB[i]) {
        return 1
      }
    }
    return arrA.length - arrB.length
  }
  let ans = [...s].sort((a, b) => a - b).map(i => a[i]).sort((arrA, arrB) => less(arrA, arrB)).flat(1)
  console.log(ans)
  while (ans.length >= 2 && ans[ans.length - 1] === ans[0]) {
    ans.pop()
  }
  let minIndex = -1; let minVal = 1e10
  for (let i = 0; i < ans.length; i++) {
    if (ans[i] < minVal) {
      minIndex = i
      minVal = ans[i]
    }
  }
  ans = [...ans.slice(minIndex), ...ans.slice(0, minIndex)]
  let ans1 = [...ans].reverse()
  ans1 = [...ans1.slice(ans1.length - 1), ...ans1.slice(0, ans1.length - 1)]
  // console.log(ans1)
  if (less(ans1, ans) < 0) ans = ans1
  console.log(ans)
  const root = new ListNode(ans[0])
  let cur = root
  for (let i = 0; i < ans.length; i++) {
    cur.next = new ListNode(ans[i])
    cur = cur.next
  }
  return root
}
module.exports = {
  solve: solve
}
