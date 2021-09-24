function findKthLargest (nums: number[], k: number): number {
  return quickSelect(0, nums.length - 1, nums.length - k + 1)
  function quickSelect (l: number, r: number, k: number): number {
    if (l >= r) return nums[l]
    let [i, j, q] = [l - 1, r + 1, nums[l + r >> 1]]
    while (i < j) {
      do i++; while (nums[i] < q)
      do j--; while (nums[j] > q)
      if (i < j) [nums[i], nums[j]] = [nums[j], nums[i]]
    }
    const cnt = j - l + 1
    if (k <= cnt) return quickSelect(l, j, k)
    else return quickSelect(j + 1, r, k - cnt)
  }
};
