#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){                             //default ctor
            _ptr = NULL;
        }
        Iterator(node<T>* p){                   //Point Iterator to where
            _ptr = p;                            //  p is pointing to
        }
        Iterator next()                     //return an iterator to the
        {                                   //  next location in the list
            return Iterator(_ptr->next);
        }                  
        bool is_null(){
            return _ptr == nullptr;
        }
        T& operator *(){                    //dereference oprator
            //assert(_ptr != null)
            //if _ptr is null, then it's zero, then it's false
            //assert(_ptr) : assert that _ptr is not ZERO: not null
            assert(_ptr);
            return _ptr->_item;             //return the T value itself
        }  
        const T& operator *()const {        //dereference oprator
            assert(_ptr);
            return _ptr->_item;;
        }


        T* operator ->(){
            assert(_ptr);
            return _ptr;                    //returns the address of the T value.
                                            //it ==> [item| serial| value|]
                                            //it -> item; //this returs the item.
        }

        const T* operator ->()const{
            assert(_ptr);
            return _ptr;
        }
        friend Iterator operator ++(Iterator& it,       //it++
                                    int unused){
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->next;
            return hold;
        }
        Iterator& operator ++(){                        //++it
            _ptr = _ptr->next;
            return *this;
        }

        friend bool operator !=(const Iterator& left,   //it != it
                                const Iterator& right){
            return left._ptr != right._ptr;
        }       
    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, 
                                        const Stack<TT>& printMe){
        outs << "Stack:Head->";
        _print_list(printMe._top);
        outs << endl;
        return outs;
    }

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

//---------------------definition----------------------
template <typename T>
Stack<T>::Stack(){
    _top = nullptr;
    _size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe){
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}
template <typename T>
Stack<T>::~Stack(){
    _clear_list(_top);
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS){
    if (this == &RHS){
        return *this;
    }
    _clear_list(_top);
    _top = nullptr;
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}

template <typename T>
T Stack<T>::top(){
    assert(_top != nullptr);
    return _top->_item;
}
template <typename T>
bool Stack<T>::empty(){
    return _top == nullptr;
}
template <typename T>
void Stack<T>::push(T item){
    _size++;
    _top = _insert_head(_top, item);
}
template <typename T>
T Stack<T>::pop(){
    // assert(_top != nullptr);
    // T pop = _top->_item;
    if (_size > 0){
        _size--;
        return _delete_node(_top, _top);
    }
    return T();
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const {              //Iterator to the head node
    return Iterator(_top);
}
template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const {                //Iterator to NULL
    return Iterator();
}


#endif //MY_STACK_H