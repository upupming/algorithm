/**
 * @param {number} width
 * @param {number} height
 */
const Robot = function (width, height) {
  this.dirs = [
    [1, 0, 'East'],
    [0, 1, 'North'],
    [-1, 0, 'West'],
    [0, -1, 'South']
  ]
  this.idx = 0
  this.pos = [0, 0]
  this.w = width
  this.h = height
  this.tot = width * 2 + (height - 2) * 2
}

/**
* @param {number} num
* @return {void}
*/
Robot.prototype.step = function (num) {
  if (num / this.tot >= 1) {
    if (this.pos[0] === 0 && this.pos[1] === 0) this.idx = 3
    if (this.pos[0] === this.w - 1 && this.pos[1] === 0) this.idx = 0
    if (this.pos[0] === this.w - 1 && this.pos[1] === this.h - 1) this.idx = 1
    if (this.pos[0] === 0 && this.pos[1] === this.h - 1) this.idx = 2
  }
  num %= this.tot
  const valid = ([i, j]) => i >= 0 && i < this.w && j >= 0 && j < this.h
  while (num--) {
    const d = this.dirs[this.idx]
    pos = [this.pos[0] + d[0], this.pos[1] + d[1]]
    if (valid(pos)) this.pos = pos
    else num++, this.idx = (this.idx + 1) % 4
  }
}

/**
* @return {number[]}
*/
Robot.prototype.getPos = function () {
  return this.pos
}

/**
* @return {string}
*/
Robot.prototype.getDir = function () {
  return this.dirs[this.idx][2]
}

/**
* Your Robot object will be instantiated and called as such:
* var obj = new Robot(width, height)
* obj.step(num)
* var param_2 = obj.getPos()
* var param_3 = obj.getDir()
*/
