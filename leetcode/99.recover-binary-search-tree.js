/*
 * @lc app=leetcode id=99 lang=javascript
 *
 * [99] Recover Binary Search Tree
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */
/**
 * @param {TreeNode} root
 * @return {void} Do not return anything, modify root in-place instead.
 */

var recoverTree = function(root) {
    // 1. 注意可以直接对 node.val 进行赋值完成交换
    // 2. 中序遍历如果出现顺序打破，进行标记，结束顺序打破再次标记
    //     例子中分别是 [3] 2 [1]；1 [3] [2] 4
    var node1, node2, inOrder = []

    // 返回此子树中序的最后一个元素
    // 不知道为什么只要将这个函数放在外面就会出错，好像是放成全局的就会默认被提前调用一次！！！
    // 我测了 PiEgg 的此题，他是把函数写在外面，也是 WA 了
    // 其他题目测了一个写在外面没问题
    var inTraversal = (root) => {
      this.cnt = this.cnt || 0
      console.log(this.cnt++)
      if (!root) return
      inTraversal(root.left)
      let prev = inOrder[inOrder.length - 1]
      console.log(`prev = ${prev && prev.val}`)
      inOrder.push(root)
      if (prev) {
        if (root.val <= prev.val) {
          console.log(prev.val, node1 && node1.val)
          node1 = node1 || prev
          console.log(prev.val, node1.val)
          node2 = root
          console.log(prev.val, root.val, node1.val, node2.val)
        }
      }
      inTraversal(root.right)
    }

    inTraversal(root)

    let tmp = node1.val
    node1.val = node2.val
    node2.val = tmp
    return root
};

// @lc code=end

