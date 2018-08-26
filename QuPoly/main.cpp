//
//  main.cpp
//  Sub-div-Solver based on CORE
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
    string qupoly_path="/Users/choukichiou/Desktop/sub/input_files/input_qupoly_system.txt";
    string var_box_path="/Users/choukichiou/Desktop/sub/input_files/input_variable_box.txt";
    string para_box_path="/Users/choukichiou/Desktop/sub/input_files/input_parameter_box.txt";
    string log_path="/Users/choukichiou/Desktop/sub/output_files/logs.txt";

    MKPred<Expr> system = input_QuPoly_system<Expr>(qupoly_path);
    BoxT<Expr> * var_box= input_box_region<Expr>(var_box_path);
    BoxT<Expr> * para_box= input_box_region<Expr>(para_box_path);
    show_QuPoly_system(system);
    show_box_region(var_box,para_box);

    queue<BoxT<Expr>> * solvable_boxes = new queue<BoxT<Expr>>;
    queue<BoxT<Expr>> * unsolvable_boxes = new queue<BoxT<Expr>>;
    Expr beta = 0.99;
    Expr theta= 0.00000000000000000000000000000000000000000000000001;
    Algorithm(system, var_box, para_box, solvable_boxes, unsolvable_boxes,log_path,beta,theta);
    Output_area(para_box,solvable_boxes, unsolvable_boxes );


    delete var_box;
    delete para_box;
    delete solvable_boxes;
    delete unsolvable_boxes;
}
