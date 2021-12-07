#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MINIMUM_CAPACITY = 3;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template <class T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<class T>
void print_array(T* a, int size, 
            int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <class T>
void print(T* a, unsigned int how_many, 
                                ostream& outs = cout);  //print array

template <class T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me'

template <class T>
int search(T* a, int size, const T& find_me);           //search for 'find_me'

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos

template <class T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template <class T>
void copy_array(T *dest, const T* src, 
                        int many_to_copy);              //copy from src to dest

template <class T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <class T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string

template <class T>
T* allocate (int capacity){
    return new T[capacity];
}

template <class T>
T* reallocate (T* a, int size, int capacity){
    T* newArray = allocate<T>(capacity);
    copy_array(newArray, a, size);  //void version
    delete[] a;
    return newArray;
}

template <class T>
void print_array(T* a, int size, int capacity, ostream& outs){
    T* walker;
    walker = a;
    cout << "( " << size << "/" << capacity << ")" << " [";
    for (int i = 0; i < size; i++){
        cout << setw(5) << *walker;
        walker++;
    }
    cout << " ]" << endl;
}

template <class T>
void print(T* a, unsigned int how_many, ostream& outs){
    T* walker;
    walker = a;
    cout << "( " << how_many << ")" << "[";
    for (int i = 0; i < how_many; i++){
        cout << setw(5) << *walker;
        walker++;
    }
    cout << " ]" << endl;
}

template <class T>
T* search_entry(T* a, int size, const T& find_me){
    T* walker;
    for (int i = 0; i < size; i++){
        walker = a + i;
        if (*walker == find_me)
            return walker;
    }
    return nullptr;
}

template <class T>
int search(T* a, int size, const T& find_me){
    T* walker = a;
    for (int i = 0; i < size; i++){
        if (*walker == find_me)
            return walker - a;
        else
            walker++;
    }
    return -1;
}

template <class T>
void shift_left(T* a, int& size, int shift_here){
    T* end = a + size - 1;
    T* start = a + shift_here;
    for (T* ptr = start; ptr <= end; ptr++){
        T* next = ptr + 1;
        *ptr = *next;
    }
    size--;
}

template <class T>
void shift_left (T* a, int& size, T* shift_here){
    T* end = a + size - 1;
    for (T* ptr = shift_here; ptr <= end; ptr++){
        T* next = ptr + 1;
        *ptr = *next;
    }
    size--;
}

template <class T>
void shift_right(T *a, int &size, int shift_here){
    T* end = a + size - 1;
    T* start = a + shift_here;
    T temp = *start;
    size++;
    for (T* ptr = start + 1; ptr <= end + 1; ptr++){
        T next = *ptr;
        *ptr = temp;
        temp = next;
    }
}

template <class T>
void shift_right (T* a, int& size, T* shift_here){
    T* end = a + size - 1;
    T temp = *shift_here;
    size++;
    for (T* ptr = shift_here + 1; ptr <= end + 1; ptr++){
        T next = *ptr;
        *ptr = temp;
        temp = next;
    }
}

template <class T>
void copy_array(T *dest, const T* src, 
                        int many_to_copy){
    T* walker1;
    const T* walker2;
    walker1 = dest;
    walker2 = src;
    for (int i = 0; i < many_to_copy; i++){
        *walker1 = *walker2;
        walker1++;
        walker2++;
    }
}


template <class T>
T* copy_array (const T* src, int size){
    T* newArray = allocate<T>(size);
    T* walker = newArray;
    const T* org = src;
    for (int i = 0; i < size; i++){
        *walker = *org;
        walker++;
        org++;
    }
    return newArray;
}

template <class T>
string array_string (const T* a, int size){
    string str = "[";
    const T* ptr = a;
    string value;
    for (int i = 0; i < size; i++){
        value = to_string(*ptr) + " ";
        str += value;
        ptr++;
    }
    str += "] [";
    str += to_string(size) + "]";
    return str;
}


#endif //ARRAY_FUNCTIONS_H