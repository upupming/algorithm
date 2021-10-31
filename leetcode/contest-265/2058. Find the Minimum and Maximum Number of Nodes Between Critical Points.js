/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {number[]}
 */
 var nodesBetweenCriticalPoints = function(head) {
  let p = head, a = [], l = []
  while (p) a.push(p.val), p = p.next
  for (let i = 0; i < a.length; i++) {
      if (i - 1 >= 0 && i + 1 < a.length) {
          if (a[i] > a[i-1] && a[i] > a[i+1]) l.push(i)
          else if (a[i] < a[i-1] && a[i] < a[i+1]) l.push(i)
      }
  }
  // console.log(l)
  if (l.length < 2) return [-1, -1]
  let ans = [1e10]
  ans[1] = l[l.length-1] - l[0]
  for (let i = 1; i < l.length; i++) ans[0] = Math.min(ans[0], l[i] - l[i-1])
  return ans
};
