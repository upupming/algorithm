function numberOfRounds (s: string, f: string): number {
  class Time {
    h: number = 0
    m: number = 0
    constructor (time?: string, h: number = 0, m: number = 0) {
      if (time) {
        this.h = parseInt(time.slice(0, 2))
        this.m = parseInt(time.slice(3, 5))
      } else {
        this.h = h
        this.m = m
      }
    }

    less (b: Time) {
      if (this.h !== b.h) return this.h < b.h
      else return this.m < b.m
    }
  }
  const [ts, tf] = [new Time(s), new Time(f)]
  if (tf.less(ts)) {
    tf.h += 24
  }
  let ans = 0
  for (let h = ts.h; h <= tf.h; h++) {
    for (let m = 0; m <= 45; m += 15) {
      const now = new Time(undefined, h, m)
      if (!now.less(ts) && !tf.less(now)) {
        ans++
      }
    }
  }
  return Math.max(ans - 1, 0)
};
