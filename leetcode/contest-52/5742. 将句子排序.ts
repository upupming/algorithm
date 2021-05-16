function sortSentence (s: string): string {
  const a = s.split(' '); const b = []
  for (const t of a) {
    b[t[t.length - 1].charCodeAt(0) - '1'.charCodeAt(0)] = t.substr(0, t.length - 1)
  }
  return b.join(' ')
};
