function maxConsecutiveAnswers (answerKey: string, k: number): number {
  const n = answerKey.length
  const calc = (dest = 'T') => {
    // cnt: flips used
    let cnt = 0; let ans = 0
    for (let i = 0, j = 0; i < n; i++) {
      while (j < n && cnt + (answerKey[j] !== dest ? 1 : 0) <= k) {
        cnt += (answerKey[j] !== dest ? 1 : 0)
        j++
      }
      ans = Math.max(ans, j - i)
      cnt -= (answerKey[i] !== dest ? 1 : 0)
    }
    return ans
  }
  return Math.max(calc('T'), calc('F'))
};
