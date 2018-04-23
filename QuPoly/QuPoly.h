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
    QuPoly(const vector<Triple<NT>> & index);
    QuPoly(const string & str);
    QuPoly(QuPoly<NT> const &temp);
    string toString(char tvar='t', char svar='s');
    QuPoly<NT> differX();
    QuPoly<NT> differY();
    QuPoly<NT> contract();
    
};

template <class NT>
QuPoly<NT>::QuPoly(){
    Triple<NT> zero;
    index.push_back(zero);
}

template <class NT>
QuPoly<NT>::QuPoly(const vector<Triple<NT>> & index_ori){
    index=index_ori;
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
QuPoly<NT> QuPoly<NT>::contract(){
    int i,j,k;
    vector<int> vec_i;
    
    for(i=0; i<int(index.size())-1; i++)
    {
        for(j=i+1;j<int(index.size());j++)
        {
            if((index[i].sdeg==index[j].sdeg) &&(index[i].tdeg==index[j].tdeg) )
            {
                vec_i.push_back(j);
            }
        }
        
        for(k=0; k< int(vec_i.size()); k++)
        {
            index[i]= index[i]+ index[vec_i[k] -k];
            index.erase(index.begin() + vec_i[k] -k );
        }
        vec_i.clear();
    }
    return *this;
}//contract(): Dealing with the product of QuPoly.






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
    QuPoly<NT> Product(product);
    Product.contract();
    
    if(int(Product.index.size())==0){
        QuPoly<NT> zero;
        return zero;
    }
    
    return Product;
}// reload *

template <class NT>
QuPoly<NT> operator+(const QuPoly<NT>& P, const QuPoly<NT>& Q)
{
    vector<Triple<NT>> sum;
    for(int i=0; i< int(P.index.size());i++)
    {
        sum.push_back(P.index[i]);
    }
    for(int i=0; i< int(Q.index.size());i++)
    {
        sum.push_back(Q.index[i]);
    }
    QuPoly<NT> Sum(sum);
    Sum.contract();
    
    if(int(Sum.index.size())==0){
        QuPoly<NT> zero;
        return zero;
    }
    
    return Sum;
}

template <class NT>
QuPoly<NT> operator-(const QuPoly<NT>& P, const QuPoly<NT>& Q)
{
    vector<Triple<NT>> dif;
    for(int i=0; i< int(P.index.size());i++)
    {
        dif.push_back(P.index[i]);
    }
    for(int i=0; i< int(Q.index.size());i++)
    {
        Triple<NT> Qindex=Q.index[i];
        Triple<NT> temp = Qindex.inverse();
        dif.push_back(temp);
    }
    QuPoly<NT> Dif(dif);
    Dif.contract();
    
    if(int(Dif.index.size())==0){
        QuPoly<NT> zero;
        return zero;
    }
    return Dif;
}



#endif /* QuPoly_h */
