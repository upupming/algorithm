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
const print = (root, s) => {
  if (!root) return
  if (s.has(root)) {
    console.log('circle', root?.val)
    return
  }
  console.log(root?.val)
  s.add(root)
  print(root.next, s)
}

const reverseEvenLengthGroups = function (head) {
  let n = 0; let p = head
  while (p) p = p.next, n++
  // 枚举长度 1, 2, 3...
  let pre = null
  for (let len = 1, a = head; a; len++) {
    const flag = Math.min(n, len) % 2 === 0
    // 开始反转从 a 开始，长度为 len 的链表，只需要反转 len-1 条边
    let newHead = a; let newTail = a
    let b = a.next
    const last = null
    for (let i = 0; i < len - 1 && b; i++) {
      c = b.next
      // console.log(len, a?.val, b?.val, c?.val)
      newTail = b
      if (flag) {
        b.next = a
      }
      a = b, b = c
    }
    if (flag) {
      [newHead, newTail] = [newTail, newHead]
    }
    // console.log(pre?.val, newHead?.val, newTail?.val)
    newTail.next = null
    if (pre) {
      pre.next = newHead
    }
    pre = newTail; a = b; n -= len
  }
  // console.log('priniting')
  // print(head, new Set())
  // console.log('priniting end')
  return head
}
