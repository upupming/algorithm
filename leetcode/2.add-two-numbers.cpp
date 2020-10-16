/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *root = new ListNode,
                *l1Next = l1 ? l1->next : nullptr,
                *l2Next = l2 ? l2->next : nullptr,
                *tmp;

        bool someNull = l1 == nullptr || l2 == nullptr;
        tmp = (l1 == nullptr ? l2 : l1);
        int sum = someNull ? tmp->val : l1->val + l2->val;

        root->val = sum % 10;
        int c = sum / 10;

        // l1 and l2 both continues
        if (l1Next && l2Next) {
            l1Next->val += c;
            root->next = addTwoNumbers(l1Next, l2Next);
        }
        // l1 and l2 both ends
        else if (!l1Next && !l2Next) {
            if (c > 0)
                root->next = new ListNode(c);
        }
        // one of l1, l2 ends
        else {
            tmp = (l1Next == nullptr ? l2Next : l1Next);
            tmp->val += c;
            root->next = addTwoNumbers(tmp, nullptr);
        }

        return root;
    }
};
// @lc code=end
