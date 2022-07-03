/**
 * @param {string} key
 * @param {string} message
 * @return {string}
 */
const decodeMessage = function (key, message) {
  const mp = {}; let c = 0
  for (const ch of key) {
    if (ch === ' ') continue
    if (mp[ch] == null) mp[ch] = String.fromCharCode((c++) + 'a'.charCodeAt(0))
  }
  return message.split('').map(x => {
    if (x === ' ') return x
    return mp[x]
  }).join('')
}
