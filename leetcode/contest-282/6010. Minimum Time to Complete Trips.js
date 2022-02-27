/**
 * @param {number[]} time
 * @param {number} totalTrips
 * @return {number}
 */
const minimumTime = function (time, totalTrips) {
  let l = 0n; let r = BigInt(1e15 + 10)
  while (l < r) {
    const mid = l + r >> 1n
    // console.log(l, r, mid)
    if (valid(mid)) r = mid
    else l = mid + 1n
  }
  function valid (mid) {
    let sum = 0n
    for (let i = 0; i < time.length; i++) {
      sum += mid / BigInt(time[i])
    }
    return sum >= totalTrips
  }
  return l
}
