/*
        -> D -> E
A -> B <-> F
       <-> G
[["JFK","BBB"],["BBB","FFF"],["FFF","BBB"],["BBB","GGG"],["GGG","BBB"],["BBB","DDD"],["DDD","EEE"]]
*/
function findItinerary (tickets: string[][]): string[] {
  const e: Record<string, string[]> = {}
  for (const [f, t] of tickets) {
    e[f] ??= [], e[f].push(t)
  }
  for (const v of Object.values(e)) v.sort((a, b) => a < b ? 1 : -1)
  console.log(e)
  const dfs = (x: string) => {
    const paths: string[][] = []
    // e: {BBB: [ 'GGG', 'FFF', 'DDD' ],}
    // 最多循环两次，第一次是 DE，第二次是 FBGB
    while (e[x]?.length) {
      // 走一个字典序最小的 y
      const y = e[x].pop()!
      paths.push(dfs(y))
    }
    const ans = [x]
    console.log(x, paths)
    while (paths.length) {
      const p = paths.pop()!
      ans.push(...p)
    }
    return ans
  }
  return dfs('JFK')
};
