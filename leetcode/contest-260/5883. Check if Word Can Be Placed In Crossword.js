/**
 * @param {character[][]} board
 * @param {string} word
 * @return {boolean}
 */
const placeWordInCrossword = function (board, word) {
  const m = board.length; const n = board[0].length
  const t = word.length
  console.log(trans(board))
  return calc(m, n, board) || calc(n, m, trans(board))
  function trans (board) {
    const ans = [...Array(n)].map(() => [])
    for (let i = 0; i < n; i++) {
      for (let j = 0; j < m; j++) {
        ans[i][j] = board[m - 1 - j][i]
      }
    }
    return ans
  }
  function calc (m, n, board) {
    for (let i = 0; i < m; i++) {
      for (let j = 0; j < n; j++) {
        if (board[i][j] !== '#') {
          let k = j
          while (k < n && board[i][k] !== '#') k++
          // [j, k-1]
          if (k - j === word.length) {
            let ok = true
            for (let l = j; l < k; l++) {
              if (board[i][l] !== ' ' && board[i][l] !== word[l - j]) {
                ok = false
                break
              }
            }
            if (ok) {
              // console.log('case 1')
              return true
            }
            ok = true
            for (let l = j; l < k; l++) {
              if (board[i][l] !== ' ' && board[i][l] !== word[t - 1 - (l - j)]) {
                ok = false
                break
              }
            }
            if (ok) {
              // console.log('case 2')
              return true
            }
          }
          j = k - 1
        }
      }
    }
    // console.log('case 3')
    return false
  }
}
