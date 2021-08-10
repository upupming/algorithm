export {}

function strWithout3a3b (a: number, b: number): string {
  if (a === 0) {
    return Array(b).fill('b').join('')
  }
  if (b === 0) {
    return Array(a).fill('a').join('')
  }
  if (a === b) {
    return Array(a).fill('ab').join('')
  }
  let l = ''
  if (a > b) {
    l = strWithout3a3b(a - 2, b - 1)
    if (l.length && l[l.length - 1] === 'a') return l + 'baa'
    else return l + 'aab'
  }
  if (a < b) {
    l = strWithout3a3b(a - 1, b - 2)
    if (l.length && l[l.length - 1] === 'a') return l + 'bba'
    else return l + 'abb'
  }
};
