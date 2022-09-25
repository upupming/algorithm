/**
 * @param {string[]} names
 * @param {number[]} heights
 * @return {string[]}
 */
const sortPeople = function (names, heights) {
  return names.map((x, idx) => [x, heights[idx]]).sort((a, b) => b[1] - a[1]).map(x => x[0])
}
