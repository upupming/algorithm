/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} left
 * @param {number} right
 * @return {ListNode}
 */
const reverseBetween = function (head, left, right) {
  const dummy = new ListNode(0, head)
  let a = dummy; let prev = null
  let i = 0
  while (i < left) {
    prev = a
    a = a.next
    i++
  }
  const last = a; let b = a.next
  while (i < right) {
    const c = b.next
    b.next = a
    a = b
    b = c
    i++
  }
  prev.next = a
  last.next = b
  return dummy.next
}
