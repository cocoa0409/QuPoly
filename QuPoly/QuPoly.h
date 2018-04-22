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
    int sdeg;
    int tdeg;
    QuPoly();
    QuPoly(const string & str);
    
    string toString(char tvar='t', char svar='s');
    
    
    
    
    
};

template <class NT>
QuPoly<NT>::QuPoly(){
}

template <class NT>
QuPoly<NT>::QuPoly(const string & str){
    BiPoly<NT> Sample(str, 't', 's');
    // detailly, API use 'x' replacing 't' and ust 'y' replacing 's'
    sdeg= Sample.getYdegree();
    
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
#endif /* QuPoly_h */
