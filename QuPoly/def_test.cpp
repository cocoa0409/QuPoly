//
//  def_test.cpp
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 22/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//
//
//  def_test.cpp
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 22/04/2018.
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
 /*
    string a;
    cin>>a;
    QuPoly<Expr> A(a);
    
    cout<<A.toString()<<endl;
    cout<<"dy:"<<A.differY().toString()<<endl;
    cout<<"dx:"<<A.differX().toString()<<endl;
  
 
  
  BiPoly<Expr> A("x+y");
  BiPoly<Expr> B("y");
  
  cout<<(A*B).toString();

    */
    
    BiPoly<Expr> A("x+y");
    BiPoly<Expr> B("y");

    Triple<Expr> A1(2,3,A);
    Triple<Expr> B2(4,17,B);
    cout<<(A1*B2).toString()<<endl;
    

 }

