function findAllRecipes (recipes: string[], ingredients: string[][], supplies: string[]): string[] {
  const e: Record<string, string[]> = {}
  const deg: Record<string, number> = {}
  const n = recipes.length
  for (let i = 0; i < n; i++) {
    const y = recipes[i]
    deg[y] ??= 0
    for (const x of ingredients[i]) {
      e[x] ??= []
      e[x].push(y)
      deg[y]++
    }
  }
  const s = new Set(supplies)
  const q = supplies
  for (const x of Object.keys(deg)) {
    if (deg[x] == null || deg[x] === 0) q.push(x)
  }
  const ans = []
  while (q.length) {
    const x = q.shift()!
    if (!s.has(x)) ans.push(x)
    for (const y of e[x] ?? []) {
      if (--deg[y] === 0) q.push(y)
    }
  }
  return ans
};
