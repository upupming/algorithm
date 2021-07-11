/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    unordered_set<int> seen;
    unordered_map<int, TreeNode*> val2Node;
    bool ok = true;
    TreeNode* valid(int val, long mn, long mx) {
        if (!ok) return nullptr;
        seen.insert(val);
        auto node = val2Node[val];
        if (node->val <= mn || node->val >= mx) {
            ok = false;
            return nullptr;
        }
        if (node->left) {
            node->left = valid(node->left->val, mn, val);
        }
        if (node->right) {
            node->right = valid(node->right->val, val, mx);
        }
        return node;
    }
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, int> deg;
        for (auto& tree : trees) {
            if (tree->left) {
                deg[tree->left->val]++;
                if (!val2Node.count(tree->left->val))
                    val2Node[tree->left->val] = tree->left;
            }
            if (tree->right) {
                deg[tree->right->val]++;
                if (!val2Node.count(tree->right->val))
                    val2Node[tree->right->val] = tree->right;
            }
            // val2Node 存储的同一个值如果在根节点和叶节点都出现过，根节点优先
            deg[tree->val] += 0;
            val2Node[tree->val] = tree;
        }
        int rootVal = -1;
        // 入度总和为 0 的值必须只有 1 个，这样才可以全部合并在一起
        for (auto& [val, cnt] : deg) {
            if (cnt == 0) {
                if (rootVal == -1) rootVal = val;
                // 两个为 0 的，不可能合并在一起
                else {
                    // cout << val << " " << cnt << endl;
                    return nullptr;
                }
            }
        }
        // 没有度为 0 的也不行
        if (rootVal == -1) {
            // cout << rootVal << endl;
            return nullptr;
        }

        TreeNode* root = valid(rootVal, LONG_MIN, LONG_MAX);
        // cout << ok << " " << seen.size() << endl;
        if (!ok || seen.size() != val2Node.size()) return nullptr;
        return root;
    }
};
