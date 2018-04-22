//
//  Triple.h
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 22/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//

#ifndef Triple_h
#define Triple_h

#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
using namespace std;

template <class NT>
class Triple{
private:
    
    
public:
    int tdeg;
    int sdeg;
    BiPoly<NT> coeffbipoly;
    Triple();
    Triple(int t,int s);
    string toString(char tvar='t', char svar='s');
    
    
};//end_of_Trple

template <class NT>
Triple<NT>::Triple(){
}

template <class NT>
Triple<NT>::Triple(int t,int s){
    tdeg=t;
    sdeg=s;
    cout<<"(t="<<t<<",s="<<s<<"):Input the coeff_BiPoly(x,y)"<<endl;
    string bipoly;
    cin>>bipoly;
    BiPoly<NT> coeffbipoly_mid(bipoly);
    coeffbipoly = coeffbipoly_mid;
}

template <class NT>
string Triple<NT>::toString(char tvar, char svar) {
    ostringstream oss;
    string s;
    oss<<"( "<<tvar<<"^"<<tdeg<<" * "<<svar<<"^"<<sdeg<<" )*["<<coeffbipoly.toString()<<"]";
    s=oss.str();
    return s;  
}//toString(Triple,t,s)
#endif /* Triple_h */
