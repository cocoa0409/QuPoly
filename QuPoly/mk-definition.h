//
//  mk-definition.h
//  Sub-div-Solver based on original CORElib
//
//  Created by 兆吉 王 on 23/04/2018.
//  Copyright © 2018 兆吉 王. All rights reserved.
//

#ifndef mk_definition_h
#define mk_definition_h

#include <CORE/CORE.h>
#include <CORE/poly/Curves.h>
#include <box.h>
#include <queue>
#include "src.h"
#include "Triple.h"
#include "QuPoly.h"
#include "CORE/CORE.h"
#include "CORE/IntervalT.h"
#include "CORE/linearAlgebraT.h"

template <typename NT>
class MKPred{
private:
    
public:
    QuPoly<NT>           fxy_;       // f(x, y)
    QuPoly<NT>           gxy_;       // g(x, y)
//MatrixT<QuPoly<NT> > jacobian_;  // jacobian matrix of F = (f, g)
    QuPoly<NT>           dfxy_dx;       // df(x, y)/dx
    QuPoly<NT>           dfxy_dy;       // df(x, y)/dy
    QuPoly<NT>           dgxy_dx;       // dg(x, y)/dx
    QuPoly<NT>           dgxy_dy;       // dg(x, y)/dy
    QuPoly<NT>              jacobian;    // the detrminant of jacobian_ matrix
    const NT            min_size_;  // minimum size of a box
//const NT            max_size_;  // if output box greater that max, keep splitting
    const unsigned int max_gen_id_;// box generation
    
    
    
    
    
    MKPred();
    MKPred(const QuPoly<NT> &fxy,
           const QuPoly<NT> &gxy, const NT &min_size,const unsigned int max_gen_id);
    bool Test1(BoxT<NT> &para_box, BoxT<NT> &var_box);
    bool Test2(BoxT<NT> &para_box, BoxT<NT> &var_box);

};



template <class NT>
MKPred<NT>::MKPred():min_size_(1), max_gen_id_(1000){
    QuPoly<NT> zero;
    fxy_=zero;
    gxy_=zero;
    dfxy_dx=zero;
    dfxy_dy=zero;
    dgxy_dx=zero;
    dgxy_dy=zero;
    jacobian=zero;
}


template <class NT>
MKPred<NT>::MKPred(const QuPoly<NT> &fxy,
       const QuPoly<NT> &gxy, const NT &min_size,const unsigned int max_gen_id) : fxy_(fxy), gxy_(gxy), min_size_(min_size), max_gen_id_(max_gen_id){
    dfxy_dx=fxy_.differX();
    dfxy_dy=fxy_.differY();
    dgxy_dx=gxy_.differX();
    dgxy_dy=gxy_.differY();
    jacobian=(dfxy_dx * dgxy_dy) - (dfxy_dy * dgxy_dx);
}

template <class NT>
bool MKPred<NT>::Test1(BoxT<NT> &para_box,BoxT<NT> &var_box)
{
    IntervalNT &x_range = var_box.x_range;
    IntervalNT &y_range = var_box.y_range;
    NT &x_l = x_range.getL();
    NT &x_r = x_range.getR();
    NT &y_l = y_range.getL();
    NT &y_r = y_range.getR();
    NT &x_mid = x_range.mid();
    NT &y_mid = y_range.mid();
//compute the jacobian at x_mid,y_mid -> a bipoly of s and t. but could still use
    //datastruct QuPoly representing.
    
    NT j00=dfxy_dx.eval(para_box,var_box);
}


template <class NT>
bool MKPred<NT>::Test2(BoxT<NT> &para_box, BoxT<NT> &var_box)
{
    if(( fxy_.eval(para_box,var_box).zero() == 0 )||( gxy_.eval(para_box,var_box).zero() == 0 ))
        return true;
    else
        return false;
}


#endif /* mk_definition_h */
