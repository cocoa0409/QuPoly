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
//members
    int tdeg;
    int sdeg;
    BiPoly<NT> coeffbipoly;
//constructors
    Triple();
    Triple(Triple<NT> const &temp);
    Triple(int t,int s);
    Triple(int t,int s, BiPoly<NT> & bipoly);
//methods
    string toString(char tvar='t', char svar='s');
    Triple<NT> differX_triple();
    Triple<NT> differY_triple();
    Triple<NT> inverse();
    IntervalT<NT> eval(BoxT<NT> & para_box, BoxT<NT> & var_box );
    Triple<NT> eval_xy(NT & x, NT & y);
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
//    cout<<"(t="<<t<<",s="<<s<<"):Input the coeff_BiPoly(x,y)"<<endl;
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
IntervalT<NT> Triple<NT>::eval(BoxT<NT> & para_box, BoxT<NT> & var_box )
{
    IntervalT<NT> t_range=para_box.x_range;
    IntervalT<NT> s_range=para_box.y_range;
    IntervalT<NT> x_range=var_box.x_range;
    IntervalT<NT> y_range=var_box.y_range;
//compute bipoly
    IntervalT<NT> xy_result=coeffbipoly.eval(x_range, y_range);
    IntervalT<NT> t_result(1),s_result(1);
//compute t
    for(int i=0;i<tdeg;i++){
        t_result *= t_range;}
//compute s
    for(int i=0;i<sdeg;i++){
        s_result *= s_range;}
    if(sdeg%2==0 && tdeg%2==0){
        IntervalT<NT> s_revised(0,s_result.getR());
        IntervalT<NT> t_revised(0,t_result.getR());
        return s_revised * t_revised * xy_result;
    }
    else
        return s_result * t_result * xy_result;
}



template <class NT>
Triple<NT> Triple<NT>::eval_xy( NT & x, NT & y )
{
    IntervalT<NT> X(x,x ),Y( y,y );
    NT R(coeffbipoly.eval(X,Y).getR()),L(coeffbipoly.eval(X,Y).getL());
    assert(R==L);
    if(R<1e-16&& R>-(1e-16))
        R=NT(0);
    BiPoly<NT> eval_poly(R);
    Triple<NT> result(tdeg,sdeg,eval_poly);
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
