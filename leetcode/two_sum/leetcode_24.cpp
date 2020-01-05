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
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *temp, *originalHead = head->next; 
        for (;head != NULL && head->next != NULL;){
            temp = head->next; 
            cout << temp->val << endl;
            head->next = head->next->next;
            temp->next = head;
            head = head->next;
            for (ListNode* tp = originalHead; tp != NULL; tp = tp->next)
                cout << tp->val << " ";
            cout << endl;
        }
        return originalHead;      
    }
};
// (1) The solution above is problematic. The reason for the problem is the pointer manipulation. Once a pointer points to some address, it 
// will always points to this physical address no matter what following operations are performed via another pointer pointing to the   
// same physical address. Pay attention to this. (2) The other thing is the whole solution is not good. Simpler solution is feasible. No
// need to deal with pointer. Just swap the valule of the node is OK.


// The follwing solution is correct and simpler.
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
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode *originalHead = head;
        for (int swapVal; head != NULL && head->next != NULL;)
        {
            swapVal = head->val;
            head->val = head->next->val;
            head->next->val = swapVal;
            head = head->next->next;
        }
        return originalHead;
    }
};
