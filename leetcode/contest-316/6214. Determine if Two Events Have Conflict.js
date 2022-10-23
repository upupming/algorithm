/**
 * @param {string[]} event1
 * @param {string[]} event2
 * @return {boolean}
 */
const haveConflict = function (e1, e2) {
  class Time {
    constructor (str) {
      this.s = str
    }

    less (t) {
      return this.s < t.s
    }
  }
  e1 = e1.map(x => new Time(x))
  e2 = e2.map(x => new Time(x))
  const f = (e1, e2) => (!e1[0].less(e2[0]) && !e2[1].less(e1[0])) || (!e1[1].less(e2[0]) && !e2[1].less(e1[1]))
  return f(e1, e2) || f(e2, e1)
}
