/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @param {number} k
 * @return {ListNode}
 */
const reverseKGroup = function (head, k) {
  let sz = 0
  let a = head
  while (a) sz++, a = a.next

  const dummy = new ListNode(0, head)
  // x: dummy, y: 1
  let x = dummy; let y = dummy.next
  for (let i = 0; i < Math.floor(sz / k); i++) {
    a = y
    let b = a.next
    // 节点个数为 k，只需要反转 k-1 次中间的边
    for (let j = 0; j < k - 1; j++) {
      const c = b.next
      b.next = a
      a = b, b = c
    }
    // dummy -> 2, 1 -> 3
    x.next = a, y.next = b
    // x: 1, y: 3
    x = y, y = y.next
  }

  return dummy.next
}
