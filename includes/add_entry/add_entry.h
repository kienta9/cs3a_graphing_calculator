#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include <iostream>
#include <iomanip>

#include "../../includes/array_functions/array_functions.h"

using namespace std;

//declaration
template<class T>
T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity);
template<class T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity);

template <class T>
T *remove_last_entry(T *list, T &popped,
                     int &size, int &capacity);

template <class T>
T *insert_entry(T *list, const T &insert_this,
                int insert_here,
                int &size,
                int &capacity);

template <class T>
T *erase_entry(T *list, int index,
               int &size, int &capacity);

//definition
template<class T>
T* add_entry(T* list, const T& new_entry,
                  int& size, int& capacity){
    if (size >= capacity){
        capacity *= 2;
        list = reallocate(list, size, capacity);
    }    
    size++;
    T* walker = list + size - 1;
    *walker = new_entry;
    return list;
}

template<class T>
T* remove_entry(T* list, const T& delete_me,
                     int& size, int& capacity){
    T* walker = list;
    for (int i = 0; i < size; i++){
        if (walker == search_entry(list, size, delete_me)){
            shift_left(list, size, walker);
        }
        walker++;
    }
    if ((size <= (capacity * 1/4)) && (capacity/2 >= MINIMUM_CAPACITY)){
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }
    return list;
}

template <class T>
T *remove_last_entry(T *list, T &popped,
                     int &size, int &capacity){
    T* walker = list + size - 1;
    popped = *walker;
    shift_left(list, size, walker);
    if ((size <= (capacity * 1/4)) && (capacity/2 >= MINIMUM_CAPACITY)){
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }
    return list;
}

template <class T>
T *insert_entry(T *list, const T &insert_this,
                int insert_here,
                int &size,
                int &capacity){
    if (size >= capacity){
        capacity *= 2;
        list = reallocate(list, size, capacity);
    }   
    T* walker = list + insert_here;
    T* insert = walker;
    shift_right(list, size, walker);
    *insert = insert_this;
    return list;
}

template <class T>
T *erase_entry(T *list, int index,
               int &size, int &capacity){
    T* walker = list + index;
    shift_left(list, size, walker);
    if ((size <= (capacity * 1/4)) && (capacity/2 >= MINIMUM_CAPACITY)){
        capacity /= 2;
        list = reallocate(list, size, capacity);
    }
    return list;
}

#endif //ADD_ENTRY_H