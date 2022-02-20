/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
const mergeNodes = function (h) {
  const v = []
  let tmp = 0
  h = h.next
  while (h) {
    if (h.val === 0) v.push(tmp), tmp = 0
    else tmp += h.val
    h = h.next
  }
  h = new ListNode(v[0])
  const ans = h
  for (let i = 1; i < v.length; i++) {
    h.next = new ListNode(v[i])
    h = h.next
  }
  h.next = null
  return ans
}
