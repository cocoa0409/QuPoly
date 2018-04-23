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
    Triple(Triple<NT> const &temp);
    Triple(int t,int s);
    Triple(int t,int s, BiPoly<NT> & bipoly);
    
    
    string toString(char tvar='t', char svar='s');
    Triple<NT> differX_triple();
    Triple<NT> differY_triple();
    
    
};//end_of_Trple

template <class NT>
Triple<NT>::Triple(){
    tdeg=0;
    sdeg=0;
    coeffbipoly="0";
}

template <class NT>
Triple<NT>::Triple(Triple<NT> const &temp){
    tdeg= temp.tdeg;
    sdeg= temp.sdeg;
    coeffbipoly= temp.coeffbipoly;
}//copy costructor

template <class NT>
Triple<NT>::Triple(int t,int s){
    tdeg=t;
    sdeg=s;
    cout<<"(t="<<t<<",s="<<s<<"):Input the coeff_BiPoly(x,y)"<<endl;
    string bipoly;
    cin>>bipoly;
    BiPoly<NT> coeffbipoly_mid(bipoly);
    coeffbipoly = coeffbipoly_mid;
}//Triple(int t,int s)

template <class NT>
Triple<NT>::Triple(int t,int s, BiPoly<NT> & bipoly){
    tdeg=t;
    sdeg=s;
    coeffbipoly = bipoly;
}//Triple(int t,int s, BiPoly<NT> & bipoly)


template <class NT>
string Triple<NT>::toString(char tvar, char svar) {
    ostringstream oss;
    string s;
    oss<<"( "<<tvar<<"^"<<tdeg<<" * "<<svar<<"^"<<sdeg<<" )*["<<coeffbipoly.toString()<<"]";
    s=oss.str();
    return s;
}//toString(Triple,t,s)


template <class NT>
Triple<NT> Triple<NT>::differX_triple(){
    Triple<NT> resu(tdeg,sdeg, coeffbipoly.differentiateX());
    return resu;
}//differX_triple()

template <class NT>
Triple<NT> Triple<NT>::differY_triple(){
    Triple<NT> resu(tdeg,sdeg, coeffbipoly.differentiateY());
    return resu;
}//differY_triple()






template <class NT>
Triple<NT> operator*(const Triple<NT>& P, const Triple<NT>& Q)
{
    BiPoly<NT> pro_poly=P.coeffbipoly * Q.coeffbipoly;
    Triple<NT> product(P.tdeg+Q.tdeg, P.sdeg+Q.sdeg ,pro_poly);
    return product;
}

#endif /* Triple_h */
