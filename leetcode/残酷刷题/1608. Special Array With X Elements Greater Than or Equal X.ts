function specialArray (nums: number[]): number {
  nums.sort((a, b) => a - b)
  // cnt[i] 表示 >= i 的数字个数
  const cnt = Array<number>(1002).fill(0)
  for (let i = 1000, j = nums.length - 1; i >= 0; i--) {
    cnt[i] += cnt[i + 1]
    while (nums[j] === i) {
      cnt[i]++
      j--
    }
  }
  for (let i = 0; i < cnt.length; i++) {
    if (cnt[i] === i) return i
  }
  return -1
};
