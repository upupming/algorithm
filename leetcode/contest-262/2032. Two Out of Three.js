/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @param {number[]} nums3
 * @return {number[]}
 */
 var twoOutOfThree = function(nums1, nums2, nums3) {
  const a = new Set()
  const b = {}
  for (x of new Set(nums1)) {
      b[x] ??= 0, b[x] += 1
  }
      for (x of new Set(nums2)) {
      b[x] ??= 0, b[x] += 1
  }
      for (x of new Set(nums3)) {
      b[x] ??= 0, b[x] += 1
  }
      for (const x in b) if (b[x] >= 2) a.add(x)
  return [...a]
};
