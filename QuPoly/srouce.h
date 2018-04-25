//
//  srouce.h
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 25/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//

#ifndef srouce_h
#define srouce_h

#ifndef CORE_LEVEL
#   define CORE_LEVEL 3  // N=1,2,3.  Defaults to N=3 if omitted
#endif
#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
#include <ctime>
#include "src.h"
#include "QuPoly.h"
#include "mk-definition.h"
#include "Stack.h"

template <class NT>
MKPred<NT> input_QuPoly_system()
{
    string a;
    cout<<"input step(1)  F : Discard all (x,y) of F as (t,s) form:| ";
    cin>>a;
    QuPoly<NT> F(a);
    cout<<"input step(1)  G : Discard all (x,y) of G as (t,s) form:| ";
    cin>>a;
    QuPoly<NT> G(a);
    MKPred<NT> system(F,G);
    cout<<endl<<" F:"<<system.fxy_.toString()<<endl;
    cout<<" G:"<<system.gxy_.toString()<<endl<<endl;
    /*
    cout<<"output dF/dx:"<<system.dfxy_dx.toString()<<endl;
    cout<<"output dF/dy:"<<system.dfxy_dy.toString()<<endl;
    cout<<"output dG/dx:"<<system.dgxy_dx.toString()<<endl;
    cout<<"output dG/dy:"<<system.dgxy_dy.toString()<<endl;
    */
    return system;
}




template <class NT>
BoxT<NT>* input_box_region(string s)
{
    cout<<"input step(2)  "<<s<<" box :" <<endl;
    string temp1,temp2;
    if(s=="varible")
    {
        cout<<"  <(> x )  =";
        cin>>temp1;
        cout<<"  ( x <)>  =";
        cin>>temp2;
        IntervalT<NT> XRegion(temp1,temp2);
    
        cout<<"  <(> y )  =";
        cin>>temp1;
        cout<<"  ( y <)>  =";
        cin>>temp2;
        IntervalT<NT> YRegion(temp1,temp2);
        return ( new BoxT<NT>(0,XRegion,YRegion));
    }
    else
    {
        cout<<"  <(> t )  =";
        cin>>temp1;
        cout<<"  ( t <)>  =";
        cin>>temp2;
        IntervalT<NT> XRegion(temp1,temp2);
        cout<<"  <(> s )  =";
        cin>>temp1;
        cout<<"  ( s <)>  =";
        cin>>temp2;
        IntervalT<NT> YRegion(temp1,temp2);
        return ( new BoxT<NT>(0,XRegion,YRegion));
    }
}

template <class NT>
void show_QuPoly_system(MKPred<NT> & system)
{
    cout<<endl<<"   &&&&& QuPoly system &&&&&   "<<endl;
    cout<<" / "<<endl;
    cout<<"| "<<system.fxy_.toString()<<" = 0"<<endl;
    cout<<"| "<<system.gxy_.toString()<<" = 0"<<endl;
    cout<<" \\ "<<endl;
}

template <class NT>
void show_box_region(BoxT<NT> * var_box,BoxT<NT> * para_box)
{
    cout<<"   &&&&&  Box  region  &&&&&   "<<endl;
    cout<<" / "<<endl;
    cout<<"| varible box: (x,y) in"<<*var_box<<endl;
    cout<<"| parameter box: (t,s) in"<<*para_box<<endl;
    cout<<" \\ "<<endl;
}


template <class NT>
void Algorithm( MKPred<NT> system , BoxT<NT> * var_box, BoxT<NT> * para_box , queue<BoxT<NT>> * solvable_boxes , queue<BoxT<NT>> * unsolvable_boxes )
{
    NT beta = 0.01;
    NT theta= 0.0000000000001;
    queue<BoxT<NT>> Ppara;
//1
    Ppara.push( *var_box );
//2
    while(beta < )
    
    
    
    
    
    
}


#endif /* srouce_h */
