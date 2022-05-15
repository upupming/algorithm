function Node (start, end) {
  this.val = 0
  this.start = start
  this.end = end
  this.left = null
  this.right = null
}

function SegmentTree (start, end) {
  this.root = new Node(start, end)
}

SegmentTree.prototype.update = function (start, end) {
  this.updateNode(this.root, start, end)
}

SegmentTree.prototype.updateNode = function (node, start, end) {
  if (!node) {
    return
  }
  if (start > node.end || end < node.start) {

  } else if (start <= node.start && end >= node.end) {
    node.val = node.end - node.start + 1
  } else {
    this.pushdown(node)
    this.updateNode(node.left, start, end)
    this.updateNode(node.right, start, end)
    this.pushup(node)
  }
}

SegmentTree.prototype.pushdown = function (node) {
  if (!node) {
    return
  }
  const mid = Math.floor((node.start + node.end) / 2)
  if (!node.left) {
    node.left = new Node(node.start, mid)
  }
  if (!node.right) {
    node.right = new Node(mid + 1, node.end)
  }
  if (node.val === (node.end - node.start + 1)) {
    node.left.val = mid - node.start + 1
    node.right.val = node.end - mid
  }
}

SegmentTree.prototype.pushup = function (node) {
  node.val = node.left.val + node.right.val
}

SegmentTree.prototype.query = function (start, end) {
  return this.queryNode(this.root, start, end)
}

SegmentTree.prototype.queryNode = function (node, start, end) {
  if (!node) {
    return 0
  }
  if (start > node.end || end < node.start) {
    return 0
  } else if (start <= node.start && end >= node.end) {
    return node.val
  } else {
    this.pushdown(node)
    return this.queryNode(node.left, start, end) + this.queryNode(node.right, start, end)
  }
}

const CountIntervals = function () {
  this.tree = new SegmentTree(0, 1e9)
}

/**
 * @param {number} left
 * @param {number} right
 * @return {void}
 */
CountIntervals.prototype.add = function (left, right) {
  this.tree.update(left, right)
}

/**
 * @return {number}
 */
CountIntervals.prototype.count = function () {
  return this.tree.query(0, 1e9)
}

// 作者：scnu_evan
// 链接：https://leetcode.cn/circle/discuss/h00hT2/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
