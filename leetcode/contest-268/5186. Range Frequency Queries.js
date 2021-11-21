/**
 * @param {number[]} arr
 */
const RangeFreqQuery = function (arr) {
  this.m = []
  const n = arr.length
  for (let i = 0; i < n; i++) {
    const x = arr[i]
    this.m[x] ??= []
    this.m[x].push(i)
  }
  // console.log(this.m)
}

/**
* @param {number} left
* @param {number} right
* @param {number} value
* @return {number}
*/
RangeFreqQuery.prototype.query = function (s, e, x) {
  if (this.m[x] == undefined) return 0
  const idx = this.m[x]
  // console.log(x, idx)
  // 找到 >= s 的最前面的一个下标
  let [l, r] = [0, idx.length - 1]
  while (l < r) {
    const mid = l + r >> 1
    if (idx[mid] >= s) r = mid
    else l = mid + 1
  }
  if (idx[l] < s) return 0
  const u = l;
  [l, r] = [0, idx.length - 1]
  // 找到 <= e 的最后面的一个下标
  while (l < r) {
    const mid = l + r + 1 >> 1
    if (idx[mid] <= e) l = mid
    else r = mid - 1
  }
  if (idx[l] > e) return 0
  const v = l
  // console.log(idx, v, u)
  return v - u + 1
}

/**
* Your RangeFreqQuery object will be instantiated and called as such:
* var obj = new RangeFreqQuery(arr)
* var param_1 = obj.query(left,right,value)
["RangeFreqQuery","query","query","query","query"]
[[[1,1,1,2,2]],[0,1,2],[0,2,1],[3,3,2],[2,2,1]]
*/
