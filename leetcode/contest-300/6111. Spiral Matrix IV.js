/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {number} m
 * @param {number} n
 * @param {ListNode} head
 * @return {number[][]}
 */
const spiralMatrix = function (m, n, h) {
  const ans = Array(m).fill(0).map(() => Array(n).fill(-1))
  let i = 0; let j = 0
  const dx = [0, 1, 0, -1]; const dy = [1, 0, -1, 0]; let cd = 0
  while (h) {
    ans[i][j] = h.val
    let ni = i + dx[cd]; let nj = j + dy[cd]
    if (ni < 0 || ni >= m || nj < 0 || nj >= n || ans[ni][nj] !== -1) cd = (cd + 1) % 4
    ni = i + dx[cd], nj = j + dy[cd]
    i = ni, j = nj
    h = h.next
  }
  return ans
}
