/**
 * @param {number} size
 */
let tmp = []
let cnt = []
let s = 0
let f = false
const Bitset = function (size) {
  tmp = Array(size).fill(0)
  cnt = [size, 0]
  s = size
  f = false
}

/**
  * @param {number} idx
  * @return {void}
  */
Bitset.prototype.fix = function (idx) {
  let old = tmp[idx]
  if (f) old = 1 - old
  tmp[idx] = f ? 0 : 1
  if (old === 0) {
    cnt[f ? 1 : 0]--, cnt[f ? 0 : 1]++
  }
}

/**
  * @param {number} idx
  * @return {void}
  */
Bitset.prototype.unfix = function (idx) {
  let old = tmp[idx]
  if (f) old = 1 - old
  tmp[idx] = f ? 1 : 0
  if (old === 1) {
    cnt[f ? 0 : 1]--, cnt[f ? 1 : 0]++
  }
}

/**
  * @return {void}
  */
Bitset.prototype.flip = function () {
  f = !f
}

/**
  * @return {boolean}
  */
Bitset.prototype.all = function () {
  return cnt[f ? 0 : 1] === s
}

/**
  * @return {boolean}
  */
Bitset.prototype.one = function () {
  return cnt[f ? 0 : 1] > 0
}

/**
  * @return {number}
  */
Bitset.prototype.count = function () {
  return cnt[f ? 0 : 1]
}

/**
  * @return {string}
  */
Bitset.prototype.toString = function () {
  return tmp.map(x => f ? (1 - x) : x).join('')
}

/**
  * Your Bitset object will be instantiated and called as such:
  * var obj = new Bitset(size)
  * obj.fix(idx)
  * obj.unfix(idx)
  * obj.flip()
  * var param_4 = obj.all()
  * var param_5 = obj.one()
  * var param_6 = obj.count()
  * var param_7 = obj.toString()
  ["Bitset","flip","unfix","all","fix","fix","unfix","all","count","toString","toString","toString","unfix","flip","all","unfix","one","one","all","fix","unfix"]
 [[2],[],[1],[],[1],[1],[1],[],[],[],[],[],[0],[],[],[0],[],[],[],[0],[0]]
  */
