//
//  main.cpp
//
//  Created by Siddharth Bhasin
//

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    
    ListNode(int val)
    : val(val)
    , next(nullptr)
    {}
};

struct List {
    using ListAddBehaviorType = std::function<ListNode*(ListNode*, int)>;
    
    ListNode *head;
    ListAddBehaviorType listAddBehavior;
    
    List(const ListAddBehaviorType& listAddBehavior)
    : head(nullptr)
    , listAddBehavior(listAddBehavior)
    {}
    
    void print() {
        auto cur = head;
        while(cur) {
            std::cout << cur->val << " ";
            cur = cur->next;
        }
        std::cout << "\n";
    }
    
    void addInSortedList(int v) {
        head = listAddBehavior(head, v);
    }
};

ListNode* SimpleListSortedAdd(ListNode* head, int v) {
    ListNode *newNode = new ListNode(v);
    
    ListNode *prev = nullptr, *cur = head;
    
    while(cur && cur->val < v) {
        prev = cur;
        cur = cur->next;
    }
    
    if(prev == nullptr) {
        newNode->next = head;
        head = newNode;
    } else if(cur == nullptr) {
        prev->next = newNode;
    } else {
        newNode->next = cur;
        prev->next = newNode;
    }
    return head;
}

ListNode* CleanListSortedAdd(ListNode* head, int v) {
    ListNode *newNode = new ListNode(v);
    
    ListNode **indirect = &head;
    while((*indirect) && (*indirect)->val < v) {
        indirect = &(*indirect)->next;
    }
    newNode->next = *indirect;
    *indirect = newNode;
    return head;
}


int main(int argc, const char * argv[]) {

    List l(CleanListSortedAdd); // Can substitute with SimpleListSortedAdd
    
    l.addInSortedList(4);
    l.print(); // [4]
    
    l.addInSortedList(2);
    l.print(); // [2, 4]
    
    l.addInSortedList(3);
    l.addInSortedList(5);
    l.addInSortedList(1);
    
    l.print(); // [1, 2, 3, 4, 5]
    
}