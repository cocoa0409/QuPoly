//
//  main.cpp
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
#include <ctime>
#include "src.h"
#include "QuPoly.h"
#include "mk-definition.h"
#include "Stack.h"
#include "srouce.h"

int main(){
    
    MKPred<Expr> system = input_QuPoly_system<Expr>();
    BoxT<Expr> * var_box= input_box_region<Expr>("varible");
    BoxT<Expr> * para_box= input_box_region<Expr>("parameter");
    show_QuPoly_system(system);
    show_box_region(var_box,para_box);

    
    queue<BoxT<Expr>> * solvable_boxes = new queue<BoxT<Expr>>;
    queue<BoxT<Expr>> * unsolvable_boxes = new queue<BoxT<Expr>>;
    
    
    Algorithm(system, var_box, para_box, solvable_boxes, unsolvable_boxes);
    Output_area(solvable_boxes, unsolvable_boxes );
    
    
    delete var_box;
    delete para_box;
    delete solvable_boxes;
    delete unsolvable_boxes;
     
  /*
    Stack<BoxT<Expr>> A;
    IntervalT<Expr> x(1,2);
    IntervalT<Expr> y(1,2);
    IntervalT<Expr> t(0.3,1);
    IntervalT<Expr> s(0.1,0.6);
    BoxT<Expr> var_box(1,x,y);
    BoxT<Expr> para_box(1,t,s);
    A.push(var_box);
    A.push(para_box);
    cout<<box_area(var_box)<<endl<<box_area(para_box)<<endl;
    cout<<min_box_area(A);
    cout<<A.size();
    Stack<BoxT<Expr>> A1=A;


*/
}
