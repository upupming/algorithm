function minCost (maxTime: number, edges: number[][], passingFees: number[]): number {
  class ListNode<T = number> {
    value: T | undefined
    next: ListNode<T> | null
    constructor (val: T | undefined = undefined, next = null) {
      this.value = val
      this.next = next
    }
  }
  class Queue<T=number> {
    lead: ListNode<T>
    tail: ListNode<T>
    #size: number
    constructor (collection: T[] = []) {
      this.lead = new ListNode<T>()
      this.tail = this.lead
      this.#size = 0
      for (const item of collection) this.push(item)
    }

    size (): number {
      return this.#size
    }

    push (value: T): void {
      this.tail = this.tail.next = new ListNode(value)
      this.#size++
    }

    back (): T {
      return this.tail.value!
    }

    shift (): T | undefined {
      if (!this.#size) return undefined
      const first = this.lead.next!
      this.lead.next = first.next
      this.#size--
      if (this.#size === 0) this.tail = this.lead
      return first.value
    }

    front (): T | undefined {
      if (!this.#size) return undefined
      return this.lead.next!.value
    }

    * values (): Generator<T, void, void> {
      let node = this.lead.next
      while (node) {
        yield node.value!
        node = node.next
      }
    }
  }

  const n = passingFees.length
  const m = edges.length
  // dp[city][time] = fee
  const dp: number[][] = [...Array(n)].map(() => Array(maxTime + 1).fill(1e9))

  const head = new Array<number>(n + 1).fill(0)
  const ver = new Array<number>(m + 1).fill(0)
  const edge = new Array<number>(m + 1).fill(0)
  const next = new Array<number>(m + 1).fill(0)
  let tot = 0
  function add (x: number, y: number, z: number) {
    ver[++tot] = y
    edge[tot] = z
    next[tot] = head[x]
    head[x] = tot
  }

  for (const e of edges) {
    add(e[0], e[1], e[2])
    add(e[1], e[0], e[2])
  }

  const q = new Queue<number[]>()
  dp[0][0] = passingFees[0]
  q.push([0, 0])
  while (q.size()) {
    const [city, time] = q.shift()!
    for (let i = head[city]; i; i = next[i]) {
      const [nextCity, nextTime] = [ver[i], time + edge[i]]
      if (nextTime > maxTime) continue
      if (dp[nextCity][nextTime] > dp[city][time] + passingFees[nextCity]) {
        dp[nextCity][nextTime] = dp[city][time] + passingFees[nextCity]
        q.push([nextCity, nextTime])
      }
    }
  }
  let ans = 1e9
  for (let time = 0; time <= maxTime; time++) {
    ans = Math.min(ans, dp[n - 1][time])
  }
  return ans === 1e9 ? -1 : ans
};
