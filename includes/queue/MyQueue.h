#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator(){                  //default ctor
            _ptr = NULL;
        }
        Iterator(node<T>* p){        //Point Iterator to where
            _ptr = p;                //  p is pointing to
        }
        //...      
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
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue<T>& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        outs << "Queue:Head->";
        _print_list(printMe._front);
        outs << endl;
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

//---------------------definition----------------------
template <typename T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = nullptr;
    _rear = _copy_list(_front, copyMe._front);            
    _size = copyMe._size;
}
template <typename T>
Queue<T>::~Queue(){
    _clear_list(_front);
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if (this == &RHS){
        return *this;
    }
    _clear_list(_front);
    _front = nullptr;
    _rear = _copy_list(_front, RHS._front);                   
    _size = RHS._size;
    return *this;
}

template <typename T>
bool Queue<T>::empty(){
    return _front == nullptr;
}
template <typename T>
T Queue<T>::front(){
    return _front->_item;
}
template <typename T>
T Queue<T>::back(){
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item){
    // if (_front == nullptr){
    //     _insert_head(_front, item);
    //     _rear = _last_node(_front);
    // }
    // else{
    //     assert(_front != nullptr);
    //     _insert_after(_front, _rear, item);
    //     _rear = _last_node(_front);
    // }
    // _size++;
    _size++;
    _front == _insert_after(_front, _rear, item);
    if (_size == 1){
        _rear = _front;
    }
    else{
        _rear = _rear->next;
    }
}
template <typename T>
T Queue<T>::pop(){
    // assert(_front != nullptr);
    // T pop = _front->_item;
    // _delete_node(_front, _front);
    // _rear = _last_node(_front);
    // _size--;
    // return pop;
    if (_size > 0){
        _size--;
        if(_size == 0){
            _rear == nullptr;
        }
        return _delete_node(_front, _front);
    }
    return T();
}


template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const {            //Iterator to the head node
    return Iterator(_front);
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const {              //Iterator to NULL
    return Iterator();
}
template <typename T>
void Queue<T>::print_pointers(){

}


#endif //MY_QUEUE_H