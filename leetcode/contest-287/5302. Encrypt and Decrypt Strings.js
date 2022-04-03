/**
 * @param {character[]} keys
 * @param {string[]} values
 * @param {string[]} dictionary
 */
const Encrypter = function (keys, values, dictionary) {
  this.km = {}
  this.keys = keys
  this.values = values
  this.ds = new Set(dictionary)
  for (let i = 0; i < keys.length; i++) {
    this.km[keys[i]] = i
  }
}

/**
* @param {string} word1
* @return {string}
*/
Encrypter.prototype.encrypt = function (word1) {
  let ans = ''
  for (const ch of word1) {
    const i = this.km[ch]
    ans += this.values[i]
  }
  return ans
}

/**
* @param {string} word2
* @return {number}
*/
Encrypter.prototype.decrypt = function (word2) {
  let ans = 0
  for (const d of this.ds) {
    let idx = 0
    let ok = true
    for (let b = 0; b < d.length; b++) {
      const ch = d[b]
      const i = this.km[ch]
      const p = this.values[i]
      for (let j = 0; j < p.length; j++) {
        if (p[j] === word2[idx]) idx++
        else {
          ok = false
          break
        }
      }
    }
    if (ok && idx === word2.length) {
      ans += ok
    }
  }
  return ans
}

/**
* Your Encrypter object will be instantiated and called as such:
* var obj = new Encrypter(keys, values, dictionary)
* var param_1 = obj.encrypt(word1)
* var param_2 = obj.decrypt(word2)
*/
