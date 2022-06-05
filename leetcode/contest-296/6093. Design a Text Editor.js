
const TextEditor = function () {
  this.s = ''
  this.t = ''
}

/**
* @param {string} text
* @return {void}
*/
TextEditor.prototype.addText = function (text) {
  this.s += text
}

/**
* @param {number} k
* @return {number}
*/
TextEditor.prototype.deleteText = function (k) {
  const d = Math.min(this.s.length, k)
  this.s = this.s.slice(0, this.s.length - d)
  return d
}

/**
* @param {number} k
* @return {string}
*/
TextEditor.prototype.cursorLeft = function (k) {
  const l = Math.max(0, this.s.length - k)
  this.t = this.s.slice(l) + this.t
  this.s = this.s.slice(0, l)
  return this.s.slice(Math.max(this.s.length - 10, 0))
}

/**
* @param {number} k
* @return {string}
*/
TextEditor.prototype.cursorRight = function (k) {
  const l = Math.min(k, this.t.length)
  this.s += this.t.slice(0, l)
  this.t = this.t.slice(l)
  return this.s.slice(Math.max(this.s.length - 10, 0))
}

/**
* Your TextEditor object will be instantiated and called as such:
* var obj = new TextEditor()
* obj.addText(text)
* var param_2 = obj.deleteText(k)
* var param_3 = obj.cursorLeft(k)
* var param_4 = obj.cursorRight(k)
*/
