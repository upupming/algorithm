#include <bits/stdc++.h>
using namespace std;
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
    ListNode* swapNodes(ListNode* head, int k) {
        int n = 0;
        int x, y;
        ListNode* cur = head;
        while (cur) {
            n++;
            if (n == k) x = cur->val;
            cur = cur->next;
        }
        int k2 = n - k + 1;
        cur = head, n = 0;
        while (cur) {
            n++;
            if (n == k2) y = cur->val;
            cur = cur->next;
        }
        cur = head, n = 0;
        while (cur) {
            n++;
            if (n == k) cur->val = y;
            if (n == k2) cur->val = x;
            cur = cur->next;
        }
        return head;
    }
};