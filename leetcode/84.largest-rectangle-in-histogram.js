/*
 * @lc app=leetcode id=84 lang=javascript
 *
 * [84] Largest Rectangle in Histogram
 */

// @lc code=start
/**
 * @param {number[]} heights
 * @return {number}
 */
var largestRectangleArea = function(heights) {
    let maxS = 0
    for (let i = 0; i < heights.length; i++) {
      let minHeight = heights[i]
      maxS = Math.max(maxS, heights[i])
      for (let j = i + 1; j < heights.length; j++) {
        minHeight = Math.min(minHeight, heights[j])
        maxS = Math.max(maxS, minHeight * (j - i + 1))
      }
    }
    return maxS
};
// @lc code=end

