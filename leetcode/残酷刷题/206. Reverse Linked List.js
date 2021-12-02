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
const reverseList = function (head) {
  const rIter = (head) => {
    let a = head; let b = a?.next
    if (a) a.next = null
    while (b) {
      const c = b.next
      b.next = a
      a = b, b = c
    }
    return a
  }
  const rRecur = (head) => {
    if (!head?.next) return head
    const a = head.next
    const newHead = rRecur(a)
    a.next = head
    if (head) head.next = null
    return newHead
  }
  // return rIter(head)
  return rRecur(head)
}
