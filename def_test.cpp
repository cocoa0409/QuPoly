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

int main(){
        using namespace std;

    using namespace std;
    string a;
    cin>>a;
    QuPoly<Expr> A(a);

    cout<<A.toString()<<endl;
    /*
    BiPoly<Expr>* poly_system= new BiPoly<Expr>[2];
    cout<<"*************** STEP 1: INPUT the Polynomial System ***************"<<endl;
    string Poly_string_1,Poly_string_2;
    cout<<"   please input the first polynomial of the system:"<<endl;
    cin>>Poly_string_1;
    cout<<"   please input the second polynomial of the system:"<<endl;
    cin>>Poly_string_2;
    poly_system[0]=Poly_string_1;
    poly_system[1]=Poly_string_2;
    Polynomial<BiPoly<Expr>> * coeff = new Polynomial<BiPoly<Expr>>[2];
    coeff[0]=Polynomial<BiPoly<Expr>>(1, poly_system);
    
    
    cout<<"*************** STEP 2: INPUT the Polynomial System ***************"<<endl;
    cout<<"   please input the third polynomial of the system:"<<endl;
    cin>>Poly_string_1;
    cout<<"   please input the fourth polynomial of the system:"<<endl;
    cin>>Poly_string_2;
    poly_system[0]=Poly_string_1;
    poly_system[1]=Poly_string_2;
    coeff[1]=Polynomial<BiPoly<Expr>>(1, poly_system);
    
    
    BiPoly<BiPoly<Expr>> A(1,coeff);
    delete[] coeff;
    delete[] poly_system;
    */
    
}


