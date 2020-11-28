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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode *la, *lb, *cur = list1;
        a -= 1;
        b -= a;
        while (a--) {
            cur = cur->next;
        }
        la = cur;
        while (b--) {
            cur = cur->next;
        }
        lb = cur;
        // cout << la->val << ", " << lb->val << endl;
        la->next = list2;
        cur = list2;
        while (cur->next != nullptr) cur = cur->next;
        cur->next = lb->next;
        return list1;
    }
};