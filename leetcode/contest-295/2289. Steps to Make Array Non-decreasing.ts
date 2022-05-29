function totalSteps (nums: number[]): number {
  interface MyNode {
    val: number
    next: MyNode | null
    prev: MyNode | null
  }
  const head: MyNode = {
    val: nums[0],
    next: null,
    prev: null
  }
  let p: MyNode | null = head
  for (let i = 1; i < nums.length; i++) {
    const node: MyNode = {
      val: nums[i],
      next: null,
      prev: p
    }
    p.next = node
    p = node
  }

  let toDel: MyNode[] = []
  p = head
  while (p?.next) {
    if (p.val > p.next?.val) {
      toDel.push(p.next)
    }
    p = p.next
  }

  let ans = 0
  while (toDel.length) {
    ans++
    const check: MyNode[] = []
    for (const q of toDel) {
      // console.log(ans, q.val)
      q.prev!.next = q.next
      if (q.next) q.next.prev = q.prev
      check.push(q.prev!)
    }
    toDel = []
    for (const q of check) {
      if (q.next?.val && q.val > q.next?.val) toDel.push(q.next)
    }
  }
  return ans
};
