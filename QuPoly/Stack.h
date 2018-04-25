//
//  Stack.h
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 24/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
using namespace std;


template <class NT>
class Stack{
public:
//member
    vector<NT> index;
//methods
    Stack();
    Stack(Stack<NT> & copy);
    void push(NT element);
    NT pop();
    int size();
    void clear();
};

template <class NT>
Stack<NT>::Stack(){
    index.clear();
}


template <class NT>
Stack<NT>::Stack(Stack<NT> & copy){
    for(int i=0;i<int(copy.index.size());i++)
    {
        index.push_back(copy.index[i]);
    }
}



template <class NT>
void Stack<NT>::push(NT element){
    index.push_back(element);
}

template <class NT>
NT Stack<NT>::pop(){
    NT result=index[int(index.size())-1];
    index.pop_back();
    return result;
}
template <class NT>
int Stack<NT>::size(){
    return int(index.size());
}
template <class NT>
void Stack<NT>::clear(){
    index.clear();
}


#endif /* Stack_h */
