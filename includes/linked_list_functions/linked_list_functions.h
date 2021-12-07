#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../node/node.h"

using namespace std;

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head);

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key);


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this);

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this);

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this);

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this);

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this);

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

//duplicate list and return the last node of the copy
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE>* &dest, node<ITEM_TYPE> *src);

//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines. 
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);
//Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //




//--------------------definition--------------------
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* walker = head;
    while (walker != nullptr){
        cout << *walker;
        walker = walker->next;
    }
    cout << "|||";
}

template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head){

}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key){
    node<ITEM_TYPE>* walker = head;
    while (walker != nullptr){
        if (walker->_item == key){
            return walker;
        }
        walker = walker->next;
    }
    return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this){
    node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
    temp->next = head;
    head = temp;     
    return head;                         
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this){
    if (head == nullptr || after_this == nullptr){
        head = _insert_head(head, insert_this);
    }
    else{                                
        node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
        temp->next = after_this->next;
        after_this->next = temp;
    }
    return head;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this){
    if (before_this == head || before_this == nullptr){
        head = _insert_head(head, insert_this);
    }
    else{
        node<ITEM_TYPE>* previous = _previous_node(head, before_this);
        head = _insert_after(head, previous, insert_this);
    }
    return head; 
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this){
    node<ITEM_TYPE>* walker = head;
    while (walker != nullptr){
        if (walker->next == prev_to_this){
            return walker;  //loop ends
        }
        walker = walker->next;
    }
    return nullptr;
}

template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this){
    node<ITEM_TYPE>* walker = delete_this;
    ITEM_TYPE item = walker->_item;
    if (delete_this == head){
        head = walker->next;
    }
    else{
        node<ITEM_TYPE>* previous = _previous_node(head, delete_this);
        previous->next = walker->next;
    }
    delete delete_this;
    return item;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
    if (head == nullptr){
        return nullptr;
    }
    else{
        node<ITEM_TYPE>* copy = new node<ITEM_TYPE>(head->_item);
        node<ITEM_TYPE>* walker = head;
        node<ITEM_TYPE>* w = copy;
        walker = walker->next;
        while(walker != nullptr){
            copy = _insert_after(copy, w, walker->_item);
            w = w->next;
            walker = walker->next;
        }
        return copy;
    }
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE>* &dest, node<ITEM_TYPE> *src){
    if (src == nullptr){
        return nullptr;
    }
    else{
        _clear_list(dest);
        dest = nullptr;
        dest = new node<ITEM_TYPE>(src->_item);
        node<ITEM_TYPE>* walker = src;
        node<ITEM_TYPE>* w = dest;
        walker = walker->next;
        while(walker != nullptr){
            dest = _insert_after(dest, w, walker->_item);
            if (walker->next == nullptr){
                return w;
            }
            w = w->next;
            walker = walker->next;
        }
        return dest;
    }

}

template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
    while (head != nullptr){
        _delete_node(head, head);
    }
    delete head;
}

template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
    // -----check condition------
    node<ITEM_TYPE>* w = head;
    int numOfNodes = 0;
    while (w != nullptr){
        w = w->next;
        numOfNodes++;
    }
    assert(numOfNodes > pos);
    //--------------------------
    node<ITEM_TYPE>* walker = head;
    for (int i = 0; i < pos; i++){
        walker = walker->next;
    }
    return walker->_item;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       
                                  ITEM_TYPE item,
                                  bool ascending){
    node<ITEM_TYPE>* mark = _where_this_goes(head, item, ascending);
    if (head == nullptr){
        head = _insert_head(head, item);
    }
    else{
        if (mark == nullptr){
            head = _insert_before(head, head, item);
        }
        else{
            head = _insert_after(head, mark, item);
        }
    }
    return head;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending){
    node<ITEM_TYPE>* mark = _where_this_goes(head, item, ascending);
    if (head == nullptr){
        head = _insert_head(head, item);
    }
    else{
        if (mark == nullptr){
            head = _insert_before(head, head, item);
        }
        else{
            if (mark->_item == item){
                mark->_item = mark->_item + item;
            }
            else{
                head = _insert_after(head, mark, item);
            }
        }
    }
    return head;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending){
    if (head == nullptr){
        return head;
    }
    node<ITEM_TYPE>* w1 = head;
    node<ITEM_TYPE>* w2 = w1->next;
    if (ascending){
        if (w1->_item > item){
            return nullptr;
        }
        while (w2 != nullptr){
            if (w2->_item > item){
                return w1;
            }
            w2 = w2->next;
            w1 = w1->next;
        }
    }
    else{
        if (w1->_item < item){
            return nullptr;
        }
        while (w2 != nullptr){
            if (w2->_item < item){
                return w1;
            }
            w2 = w2->next;
            w1 = w1->next;
        }
    }
    return w1;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
    node<ITEM_TYPE>* walker = head;
    while (walker != nullptr){
        if (walker->next == nullptr){
            return walker;  //loop ends
        }
        walker = walker->next;
    }
    return nullptr;
}

#endif //LINKED_LIST_FUNCTIONS