//
//  QuPoly.h
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 22/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//


#ifndef QuPoly_h
#define QuPoly_h

#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
#include "Triple.h"

using namespace std;


template <class NT>
class QuPoly{
private:
    
public:
    vector<Triple<NT>> index;
    
    QuPoly();
    QuPoly(const string & str);
    QuPoly(QuPoly<NT> const &temp);
    string toString(char tvar='t', char svar='s');
    QuPoly<NT> differX();
    QuPoly<NT> differY();
};

template <class NT>
QuPoly<NT>::QuPoly(){
    Triple<NT> zero;
    index.push_back(zero);
}

template <class NT>
QuPoly<NT>::QuPoly(QuPoly<NT> const &temp){
    index= temp.index;
}//copy costructor

template <class NT>
QuPoly<NT>::QuPoly(const string & str){
    BiPoly<NT> Sample(str, 't', 's');
    // detailly, API use 'x' replacing 't' and ust 'y' replacing 's'
    int sdeg= Sample.getYdegree();
    
    Polynomial<NT> current_poly;
    for(int i=0;i<= sdeg;i++)
    {
        current_poly=Sample.coeffX[i];
        for(int j=0;j<= current_poly.getDegree();j++)
        {
            NT current_coef=current_poly.getCoeff(j);
            if(current_coef!=NT(0)){
                cout<<"coef(s="<<i<<",t="<<j<<")!"<<endl;
                Triple<NT> current_triple(j,i);
                index.push_back(current_triple);
            }
            
        }
    }
}//QuPoly(const string & str)

template <class NT>
string QuPoly<NT>::toString(char tvar, char svar) {
    vector<Triple<NT>> duplicate_index=index;
    Triple<NT> current_triple;
    ostringstream oss;
    string s;
    for(int i=0; i<duplicate_index.size();i++){
        current_triple = duplicate_index[i];
        if(i!=0){
            oss<<"+";
        }
        oss<<current_triple.toString('t','s');
        
    }
    s=oss.str();
    return s;
}//toString(Qupoly,t,s)


template <class NT>
QuPoly<NT> QuPoly<NT>::differX(){
    QuPoly<NT> DifferX;
    for(int i=0; i < int(index.size()) ; i++)
    {
        Triple<NT> temp(index[i]);
        DifferX.index.push_back(temp.differX_triple());
    }
//simplify
    vector<int> A;
    for(int i=0; i< int(DifferX.index.size());i++)
    {
        if(DifferX.index[i].coeffbipoly.getXdegree()==-1 && DifferX.index[i].coeffbipoly.getTrueYdegree()==-1)
        {
            A.push_back(i);
        }
    }
    for(int i=0; i< int(A.size()); i++)
    {
        DifferX.index.erase(DifferX.index.begin() + A[i] -i );
    }
    if(DifferX.index.size()==0)
    {
        Triple<NT> zero;
        DifferX.index.push_back(zero);
    }
    
    return DifferX;
}//differX()

template <class NT>
QuPoly<NT> QuPoly<NT>::differY(){
    QuPoly<NT> DifferY;
    for(int i=0; i < int(index.size()) ; i++)
    {
        Triple<NT> temp(index[i]);
        DifferY.index.push_back(temp.differY_triple());
    }
//simplify
    vector<int> A;
    for(int i=0; i< int(DifferY.index.size());i++)
    {
        if(DifferY.index[i].coeffbipoly.getXdegree()==-1 && DifferY.index[i].coeffbipoly.getTrueYdegree()==-1)
        {
            A.push_back(i);
        }
    }
    for(int i=0; i< int(A.size()); i++)
    {
        DifferY.index.erase(DifferY.index.begin() + A[i] -i );
    }
    if(DifferY.index.size()==0)
    {
        Triple<NT> zero;
        DifferY.index.push_back(zero);
    }
    return DifferY;
}//differY()



template <class NT>
QuPoly<NT> operator*(const QuPoly<NT>& P, const QuPoly<NT>& Q)
{
    vector<Triple<NT>> product;
    for(int i=0; i< int(P.index.size());i++)
    {
        for(int j=0; j< int(Q.index.size());j++)
        {
            product.push_back(P.index[i]*Q.index[j]);
        }
    }
    
}

#endif /* QuPoly_h */
