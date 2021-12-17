/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {void} Do not return anything, modify head in-place instead.
 */
const reorderList = function (head) {
  let sz = 0; let a = head
  while (a) sz++, a = a.next

  a = head
  for (let i = 0; i < Math.floor((sz - 1) / 2); i++) {
    a = a.next
  }
  let head2 = a.next
  a.next = null
  head2 = reverse(head2)

  const dummy = new ListNode()
  let p = head; let q = head2; let cur = dummy
  while (p || q) {
    if (p) {
      cur.next = p
      p = p.next
      cur = cur.next
    }
    if (q) {
      cur.next = q
      q = q.next
      cur = cur.next
    }
  }
  return dummy.next
}

function reverse (head) {
  if (!head) return null
  let a = head; let b = a.next
  head.next = null
  while (b) {
    const c = b.next
    b.next = a
    a = b, b = c
  }
  return a
}
