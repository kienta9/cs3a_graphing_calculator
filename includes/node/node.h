#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>

using namespace std;

template <typename ITEM_TYPE>
struct node
{
public:
    node(){
      _item = ITEM_TYPE();  //Type() : zero for all type
      next = nullptr;
    }

    node(ITEM_TYPE item){
      _item = item;
      next = nullptr;
    }

    template <typename T>
    friend std::ostream& operator <<(std::ostream& outs,
                                const node<T> &printMe){
      outs << "[" << printMe._item << "]-> ";
      return outs;
    }

    ITEM_TYPE _item;
    node* next;
};

#endif //NODE_H