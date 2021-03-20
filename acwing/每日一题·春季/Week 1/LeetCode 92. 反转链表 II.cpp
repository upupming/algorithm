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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;

        auto dummy = new ListNode;
        dummy->next = head;
        auto start = dummy, end = dummy;
        for (int i = 0; i < left - 1; i++) {
            start = start->next;
        }
        for (int i = 0; i < right; i++) {
            end = end->next;
        }
        auto a = start->next, b = a->next, d = end->next;

        while (b != d) {
            auto c = b->next;
            b->next = a;
            a = b;
            b = c;
        }
        // 2->5
        start->next->next = d;
        // 1->4
        start->next = end;
        return dummy->next;
    }
};
