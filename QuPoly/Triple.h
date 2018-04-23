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
    Triple<NT> inverse();
    
    
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
    Triple<NT> result(tdeg,sdeg, coeffbipoly.differentiateX());
    return result;
}//differX_triple()

template <class NT>
Triple<NT> Triple<NT>::differY_triple(){
    Triple<NT> result(tdeg,sdeg, coeffbipoly.differentiateY());
    return result;
}//differY_triple()

template <class NT>
Triple<NT> Triple<NT>::inverse()
{
    BiPoly<NT> temp=coeffbipoly;
    temp.mulScalar(-1);
    Triple<NT> result(tdeg,sdeg,temp);
    return result;
}









template <class NT>
Triple<NT> operator*(const Triple<NT>& P, const Triple<NT>& Q)
{
    BiPoly<NT> pro_poly=P.coeffbipoly * Q.coeffbipoly;
    Triple<NT> product(P.tdeg+Q.tdeg, P.sdeg+Q.sdeg ,pro_poly);
    return product;
}//reload * of Triple

template <class NT>
Triple<NT> operator+(const Triple<NT>& P, const Triple<NT>& Q)
{
    assert(P.sdeg==Q.sdeg && P.tdeg==Q.tdeg);
    BiPoly<NT> sum_poly=P.coeffbipoly + Q.coeffbipoly;
    Triple<NT> sum(P.tdeg,P.sdeg, sum_poly);
    return sum;
    
}// reload + of Triple

template <class NT>
Triple<NT> operator-(const Triple<NT>& P, const Triple<NT>& Q)
{
    assert(P.sdeg==Q.sdeg && P.tdeg==Q.tdeg);
    BiPoly<NT> dif_poly=P.coeffbipoly - Q.coeffbipoly;
    Triple<NT> dif(P.tdeg,P.sdeg, dif_poly);
    return dif;
    
}// reload - of Triple














/*


//line 433 in class BiPoly

template <class NT>
BiPoly<NT> BiPoly<NT>::mulScalar_nochange( const NT & c) {
    //std::cout << " Insider mulscalr c = " << c << std::endl;
    if (c==NT(0)) {
        BiPoly<NT> zero;
        return zero;
    }
    
    vector<Polynomial<NT>> temp=coeffX;
    
    NT cc = c;
    if(c!= NT(1)){
        //        std::cout<<"Inside mulscalar constant not one" << std::endl;
        for (int i = 0; i<=ydeg ; i++)
            temp[i].mulScalar(cc);
    }
    BiPoly<NT> result(temp);
    return result;
}//mulScalar


//line 482 in class Polynomial
template <class NT>
Polynomial<NT> Polynomial<NT>::mulScalar_nochange ( const NT & c){
    
    
}

*/


#endif /* Triple_h */
