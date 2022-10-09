/**
 * @param {number} n
 * @param {number[][]} logs
 * @return {number}
 */
 var hardestWorker = function(n, logs) {
  let l = 0, mp = {}
  for (let i = 0; i < logs.length; i++) {
      logs[i].push(logs[i][1] - (logs[i-1]?.[1] ?? 0))
  }
  logs.sort((a, b) => {
      if (a[2] === b[2]) return a[0]-b[0]
      return -(a[2]-b[2])
  })
    // console.log(logs)
    return logs[0][0]
};
