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

  class AdjList {
    head: number[]
    ver: number[]
    edge: number[]
    next: number[]
    tot: number
    /**
     * @description Initialize an adjacency list
     * @param n Number of vertices
     * @param m Number of edges
     */
    constructor (n: number, m: number | undefined) {
      m ??= n
      this.head = new Array<number>(n + 1).fill(0)
      this.ver = new Array<number>(2 * (m + 1)).fill(0)
      this.edge = new Array<number>(2 * (m + 1)).fill(0)
      this.next = new Array<number>(2 * (m + 1)).fill(0)
      this.tot = 0
    }

    /**
     * @description Add an directed edge to the adjacency list, you can add two edges (ie. a to b & b to a) when constructing an undirected graph
     * @param from The starting vertex of the edge
     * @param to The ending vertex of the edge
     * @param weight The weight of the edge
    */
    add (from: number, to: number, weight: number): void {
      this.ver[++this.tot] = to
      this.edge[this.tot] = weight
      this.next[this.tot] = this.head[from]
      this.head[from] = this.tot
    }

    /**
     * @description Return a iterator to all the edges ([`to`, `weight`]) starting from `from`
     * @param from The starting vertex of the edges
    */
    * edges (from: number): Generator<[number, number]> {
      let curr = this.head[from]
      while (curr) {
        yield [this.ver[curr], this.edge[curr]]
        curr = this.next[curr]
      }
    }
  };

  const n = passingFees.length
  const m = edges.length
  const adjList = new AdjList(n, m)
  // dp[city][time] = fee
  const dp: number[][] = [...Array(n)].map(() => Array(maxTime + 1).fill(1e9))

  for (const e of edges) {
    adjList.add(e[0], e[1], e[2])
    adjList.add(e[1], e[0], e[2])
  }

  const q = new Queue<number[]>()
  dp[0][0] = passingFees[0]
  q.push([0, 0])
  while (q.size()) {
    const [city, time] = q.shift()!
    for (const e of adjList.edges(city)) {
      const [nextCity, edge] = e
      const nextTime = time + edge
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
