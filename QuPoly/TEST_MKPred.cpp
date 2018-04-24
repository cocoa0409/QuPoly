//
//  TEST_MKPred.cpp
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
    BiPoly<Expr> a1("x^2+y^2-1");
    Triple<Expr> A1(1,0,a1);
    BiPoly<Expr> a2("x^2+y^2");
    Triple<Expr> A2(2,3,a2);
    BiPoly<Expr> a3("-1");
    Triple<Expr> A3(0,4,a3);
    vector<Triple<Expr>> tempf;
    tempf.push_back(A1);
    tempf.push_back(A2);
    tempf.push_back(A3);
    
    BiPoly<Expr> a4("0");
    Triple<Expr> A4(0,5,a4);
    tempf.push_back(A4);//test for contract();
    tempf.push_back(A3);//test for clear();
    
    
    QuPoly<Expr> F(tempf);
    cout<<"F:"<<F.toString()<<endl;
    F.clear();
    cout<<"F.clear():"<<F.toString()<<endl;
    F.contract();
    cout<<"F.contract():"<<F.toString()<<endl;
    
    
    
    
    
    BiPoly<Expr> a5("x^2+xy^2-1");
    Triple<Expr> A5(1,3,a5);
    BiPoly<Expr> a6("y^2-16");
    Triple<Expr> A6(2,3,a6);
    vector<Triple<Expr>> tempg;
    tempg.push_back(A5);
    tempg.push_back(A6);
    QuPoly<Expr> G(tempg);
    
    cout<<"G:"<<G.toString()<<endl;
    cout<<"G+F:"<<(G+F).toString()<<endl;
    
    MKPred<Expr> MKF(F,G,1,1);
    IntervalT<Expr> x(1,2);
    IntervalT<Expr> y(1,2);
    IntervalT<Expr> t(0.9,1);
    IntervalT<Expr> s(0.5,0.6);
    BoxT<Expr> var_box(1,x,y);
    BoxT<Expr> para_box(1,t,s);
    cout<<"test: Test2(G,F):"<<MKF.Test2(para_box, var_box)<<endl;
    
    
}
