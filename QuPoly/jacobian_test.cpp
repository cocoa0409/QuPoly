//
//  jacobian_test.cpp
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 24/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//


#ifndef CORE_LEVEL
#   define CORE_LEVEL 3  // N=1,2,3.  Defaults to N=3 if omitted
#endif
#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
#include "src.h"
#include "QuPoly.h"
#include <ctime>

#include"mk-definition.h"

int main(){
    
    
    using namespace std;
    
    string a;
    cin>>a;
    QuPoly<Expr> A(a);
    
    cout<<"A:"<<A.toString()<<endl;
    cout<<"dy:"<<A.differY().toString()<<endl;
    cout<<"dx:"<<A.differX().toString()<<endl;
    
    cin>>a;
    QuPoly<Expr> B(a);
    cout<<"B:"<<B.toString()<<endl;
    cout<<"dy:"<<B.differY().toString()<<endl;
    cout<<"dx:"<<B.differX().toString()<<endl;
    
    cout<<"dA/dy * dB/dx:"<<(A.differY()*B.differX()).toString()<<endl;
    cout<<"dB/dy * dA/dx:"<<(A.differX()*B.differY()).toString()<<endl;
    cout<<"jacobian: "<<(A.differX()*B.differY()-A.differY()*B.differX()).toString()<<endl;
    
}
