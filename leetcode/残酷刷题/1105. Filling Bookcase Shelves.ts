function minHeightShelves (books: number[][], shelfWidth: number): number {
  const n = books.length
  // [0:i] 的最小总高度
  const minHeight = Array<number>(n).fill(1e7)
  for (let i = 0; i < n; i++) {
    let height = 0; let thickness = 0
    for (let j = i; j >= 0; j--) {
      height = Math.max(height, books[j][1])
      thickness += books[j][0]
      if (thickness <= shelfWidth) {
        minHeight[i] = Math.min(minHeight[i], (j > 0 ? minHeight[j - 1] : 0) + height)
      }
    }
  }
  return minHeight[n - 1]
};
