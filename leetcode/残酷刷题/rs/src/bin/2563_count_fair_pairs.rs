/*
/**
 * @param {number[]} nums
 * @param {number} lower
 * @param {number} upper
 * @return {number}
 */
var countFairPairs = function(nums, lower, upper) {
    const n = nums.length
    nums.sort((a, b) => a-b)
    nums[n] = 1e10
    let c = 0
    // console.log(nums)
    for (let i = 0; i < n; i++) {
        let s, t
        let l = i+1, r = n
        // 第一个 >= lower 的地方
        while (l < r) {
            const mid = l+r >> 1
            if (nums[i]+nums[mid] >= lower) r = mid
            else l = mid+1
        }
        s = l
        // 第一个 > upper 的地方
        l = 1, r = n
        while (l < r) {
            const mid = l+r >> 1
            if (nums[i]+nums[mid] > upper) r = mid
            else l = mid+1
        }
        t = l
        // 区间 [s, t)
        c += Math.max(t-s, 0)
        // console.log(i, s, t, t-s)
    }
    return c
};
*/
impl Solution {
    pub fn count_fair_pairs(nums: Vec<i32>, lower: i32, upper: i32) -> i64 {
        let n = nums.len();
        let mut nums = nums;
        nums.sort();
        nums.push(1e10 as i32);
        let mut c = 0;
        for i in 0..n {
            let mut s;
            let mut t;
            let mut l = i + 1;
            let mut r = n;
            while l < r {
                let mid = (l + r) >> 1;
                if nums[i] + nums[mid] >= lower {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            s = l;
            l = i + 1;
            r = n;
            while l < r {
                let mid = (l + r) >> 1;
                if nums[i] + nums[mid] > upper {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            t = l;
            c += t - s;
        }
        return c as i64;
    }
}
