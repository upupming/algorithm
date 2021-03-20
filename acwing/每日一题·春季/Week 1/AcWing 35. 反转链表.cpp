/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
   public:
    ListNode* reverseList_iter(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto a = head, b = head->next;
        a->next = nullptr;
        while (b) {
            auto c = b->next;
            b->next = a;
            a = b;
            b = c;
        }
        return a;
    }
    ListNode* reverseList_recur(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto tail = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return tail;
    }
    ListNode* reverseList(ListNode* head) {
        // return reverseList_iter(head);
        return reverseList_recur(head);
    }
};
