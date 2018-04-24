//
//  TEST_jacobian.cpp
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 24/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//

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
    /*一种定义方式
    string a;
    cin>>a;
    QuPoly<Expr> A(a);
    cin>>a;
    QuPoly<Expr> B(a);
    */
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

    
    
    BiPoly<Expr> a5("x^2+xy^2-1");
    Triple<Expr> A5(1,3,a5);
    BiPoly<Expr> a6("y^2-16");
    Triple<Expr> A6(2,3,a6);
    vector<Triple<Expr>> tempg;
    tempg.push_back(A5);
    tempg.push_back(A6);
    
    
    
    QuPoly<Expr> A(tempf);
    QuPoly<Expr> B(tempg);
    cout<<"A:"<<A.toString()<<endl;
    A.clear();
    cout<<"A.clear():"<<A.toString()<<endl;
    A.contract();
    cout<<"A.contract():"<<A.toString()<<endl;
    cout<<"B:"<<B.toString()<<endl;
    B.clear();
    cout<<"B.clear():"<<B.toString()<<endl;
    B.contract();
    cout<<"B.contract():"<<B.toString()<<endl;
    cout<<"G+F:"<<(A+B).toString()<<endl;
    cout<<"G-F:"<<(A-B).toString()<<endl;
    cout<<"G*F:"<<(A*B).toString()<<endl<<endl;
    
    cout<<"A:"<<A.toString()<<endl;
    cout<<"B:"<<B.toString()<<endl<<endl;
    
    cout<<"dA/dy:"<<A.differY().toString()<<endl;
    cout<<"dA/dx:"<<A.differX().toString()<<endl<<endl;
    
    
    cout<<"dB/dy:"<<B.differY().toString()<<endl;
    cout<<"dB/dx:"<<B.differX().toString()<<endl<<endl;
    
    cout<<"dA/dy * dB/dx:"<<(A.differY()*B.differX()).toString()<<endl;
    cout<<"dB/dy * dA/dx:"<<(A.differX()*B.differY()).toString()<<endl;
    cout<<"jacobian_discriminent: "<<(A.differX()*B.differY()-A.differY()*B.differX()).toString()<<endl;
    
}
