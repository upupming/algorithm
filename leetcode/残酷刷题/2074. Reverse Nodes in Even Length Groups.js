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
const reverseEvenLengthGroups = function (head) {
  let a = head; let sz = 0
  while (a) sz++, a = a.next
  console.log(sz)
  let x = null; let y = head
  for (let i = 1; sz > 0; sz -= i, i++) {
    const len = Math.min(i, sz)
    let a = y; let b = a.next
    // console.log('case1', i, len, sz, x?.val, y?.val, a?.val, b?.val)
    for (let j = 0; j < len - 1; j++) {
      if (len % 2 === 0) {
        const c = b.next
        b.next = a
        a = b, b = c
      } else {
        a = a.next
      }
    }
    if (len % 2 === 0) {
      // console.log('case2', i, sz, len, x?.val, y.val, a.val, b?.val)
      x.next = a, y.next = b
      x = y, y = x.next
    } else {
      x = a, y = x.next
    }
  }

  return head
}
