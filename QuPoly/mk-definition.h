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
    
    
    
    
    MKPred();
    MKPred(const QuPoly<NT> &fxy,
           const QuPoly<NT> &gxy);
    bool Test1(BoxT<NT> &para_box, BoxT<NT> &var_box);
    bool Test2(BoxT<NT> &para_box, BoxT<NT> &var_box);

};



template <class NT>
MKPred<NT>::MKPred(){
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
       const QuPoly<NT> &gxy) : fxy_(fxy), gxy_(gxy){
    dfxy_dx=fxy_.differX();
    dfxy_dy=fxy_.differY();
    dgxy_dx=gxy_.differX();
    dgxy_dy=gxy_.differY();
    jacobian=(dfxy_dx * dgxy_dy) - (dfxy_dy * dgxy_dx);
}

template <class NT>
bool MKPred<NT>::Test1(BoxT<NT> &para_box,BoxT<NT> &var_box)
{
    IntervalT<NT> x_range = var_box.x_range;
    IntervalT<NT> y_range = var_box.y_range;
    NT x_l = x_range.getL();
    NT x_r = x_range.getR();
    NT y_l = y_range.getL();
    NT y_r = y_range.getR();
    NT x_mid = x_range.mid();
    NT y_mid = y_range.mid();
//compute the jacobian at x_mid,y_mid -> a bipoly of s and t. but could still use
    //datastruct QuPoly representing.
    
    QuPoly<NT> j00 = dfxy_dx.eval_xy(x_mid, y_mid);
    QuPoly<NT> j01 = dfxy_dy.eval_xy(x_mid, y_mid);
    QuPoly<NT> j10 = dgxy_dx.eval_xy(x_mid, y_mid);
    QuPoly<NT> j11 = dgxy_dy.eval_xy(x_mid, y_mid);
    
    QuPoly<NT> Fxy_=fxy_ * j11 - gxy_ * j01;
    QuPoly<NT> Gxy_=gxy_ * j00 - fxy_ * j10;
    
    BoxT<NT> x_l_y(1,x_l,y_range);
    BoxT<NT> x_r_y(1,x_r,y_range);
    BoxT<NT> x_y_l(1,x_range,y_l);
    BoxT<NT> x_y_r(1,x_range,y_r);
    
    IntervalT<NT> I_l, I_r, I_u, I_d;
    I_l=Fxy_.eval(para_box, x_l_y);
    I_r=Fxy_.eval(para_box, x_r_y);
    I_d=Gxy_.eval(para_box, x_y_l);
    I_u=Gxy_.eval(para_box, x_y_r);
    
    
    if (!I_l.zero() && !I_r.zero() && !I_d.zero() && !I_u.zero()) {
        //        std::cout << "Boundaries have fixed sign "<< std::endl;
        
        if (sign(I_l.getR()) *sign(I_r.getR()) < 0 &&
            sign(I_d.getR()) *sign(I_u.getR()) < 0 )  {
            //            std::cout <<" MK Test successful " << std::endl;
            return true;
        }else if (sign(I_l.getR()) *sign(I_r.getR()) > 0 ||
                  sign(I_d.getR()) *sign(I_u.getR()) > 0 ) {
            return false;
        }
        else {
            return false;
        }
    }
    
    if (!I_l.zero() && !I_r.zero()) {
        if (sign(I_l.getR())*sign(I_r.getR()) > 0) {
            return false;
        }
    }
    
    if (!I_d.zero() && !I_u.zero()) {
        if (sign(I_d.getR())*sign(I_u.getR()) > 0) {
            return false;
        }
    }
    
   //补充 针对0
    if ( ( I_r.getR()<=0 && I_l.getL()>=0 ) ||  ( I_r.getL()>=0 && I_l.getR()<=0 ) ){
        if( ( I_u.getR()<=0 && I_d.getL()>=0 ) ||  ( I_u.getL()>=0 && I_d.getR()<=0 ) ){
            return true;
        }
    }
    
    return false;
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
