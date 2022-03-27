/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[][]}
 */
const findDifference = function (a1, a2) {
  const s1 = new Set([...a1])
  const s2 = new Set([...a2])
  const x1 = new Set(); const x2 = new Set()
  for (const x of a1) if (!s2.has(x)) x1.add(x)
  for (const x of a2) if (!s1.has(x)) x2.add(x)
  return [[...x1], [...x2]]
}
