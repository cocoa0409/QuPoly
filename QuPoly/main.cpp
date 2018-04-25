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
    Output_area(para_box,solvable_boxes, unsolvable_boxes );
    
    
    delete var_box;
    delete para_box;
    delete solvable_boxes;
    delete unsolvable_boxes;
}
