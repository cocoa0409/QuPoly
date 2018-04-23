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



#endif /* mk_definition_h */
