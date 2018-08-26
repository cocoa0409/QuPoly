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
#include <fstream>
template <class NT>
MKPred<NT> input_QuPoly_system(string path)
{
    string temp;
    ifstream inputfile_qupoly_system;
    inputfile_qupoly_system.open(path);
//extract F from file
    getline(inputfile_qupoly_system, temp);
    QuPoly<NT> F(temp,inputfile_qupoly_system);
//extract dividing line from file
    getline(inputfile_qupoly_system, temp);
    assert(temp=="");
//extract G from file
    getline(inputfile_qupoly_system, temp);
    QuPoly<NT> G(temp,inputfile_qupoly_system);
    
    MKPred<NT> system(F,G);
//    cout<<" F:"<<system.fxy_.toString()<<endl;
//    cout<<" G:"<<system.gxy_.toString()<<endl<<endl;
    inputfile_qupoly_system.close();
    return system;
}




template <class NT>
BoxT<NT>* input_box_region(string path)
{
    string temp1,temp2;
    ifstream inputfile_box;
    inputfile_box.open(path);
    getline(inputfile_box,temp1);
    getline(inputfile_box,temp2);
    IntervalT<NT> XRegion(temp1,temp2);
    
    getline(inputfile_box,temp1);
    getline(inputfile_box,temp2);
    IntervalT<NT> YRegion(temp1,temp2);
    inputfile_box.close();
    return ( new BoxT<NT>(0,XRegion,YRegion));
}

template <class NT>
void show_QuPoly_system(MKPred<NT> & system)
{
    cout<<"   &&&&& QuPoly system &&&&&   "<<endl;
    cout<<" / "<<endl;
    cout<<"| "<<system.fxy_.toString()<<" = 0"<<endl;
    cout<<"| "<<system.gxy_.toString()<<" = 0"<<endl;
    cout<<" \\ "<<endl;
    cout<<endl<<"   &&&&& QuPoly system &&&&&   "<<endl;
}

template <class NT>
void show_box_region(BoxT<NT> * var_box,BoxT<NT> * para_box)
{
    cout<<"   &&&&&  Box  region  &&&&&   "<<endl;
    cout<<" / "<<endl;
    cout<<"| varible box: (x,y) in "<<*var_box<<endl;
    cout<<"| parameter box: (t,s) in "<<*para_box<<endl;
    cout<<" \\ "<<endl;
    cout<<"   &&&&&  Box  region  &&&&&   "<<endl<<endl;
}

template <class NT>
NT box_area(BoxT<NT> var_box){
    return (var_box.width() * var_box.height());
}

template <class NT>
NT boxes_area(queue<BoxT<NT>> * boxes_queue)
{
    NT result=0;
    for(int i=0;i<int(boxes_queue->size());i++)
    {
        result += box_area(boxes_queue->front());
        boxes_queue->push(boxes_queue->front());
        boxes_queue->pop();
    }
    return result;
}


template <class NT>
NT min_box_area(Stack<BoxT<NT>> & stack)
{
    /*
    Stack<BoxT<NT>> boxes_stack=stack;
    NT result=NT(1000000);
    NT temp;
    Expr j=int(boxes_stack.size());
    for(int i=0;i<j;i++)
    {
        temp=box_area(boxes_stack.pop());
        if(temp < result)
        {
            result = temp;
        }
    }
     */
    return box_area(stack.index[stack.index.size()-1]);
}




template <class NT>
void Algorithm( MKPred<NT> system , BoxT<NT> * var_box, BoxT<NT> * para_box , queue<BoxT<NT>> * solvable_boxes , queue<BoxT<NT>> * unsolvable_boxes,string output_path,NT beta,NT theta)
{
    Stack<BoxT<NT>> Svar;
    int i;
    bool flag;
    NT total_area=box_area(*para_box);
    ofstream out;
    out.open(output_path);
//1
    queue<BoxT<NT>> Ppara;
    Ppara.push( *para_box );
//2
    while( beta > (boxes_area(solvable_boxes)+boxes_area(unsolvable_boxes))/total_area )
    {
//3
        BoxT<Expr> * pbar = new BoxT<Expr>(Ppara.front());
        Ppara.pop();
//4
        Svar.clear();
        Svar.push( *var_box );
//5
        flag=false;
//6
        while( min_box_area(Svar)> theta )
        {
//7
            BoxT<Expr>* vbar=new BoxT<Expr>(Svar.pop());
//8
            if(system.Test1(*pbar, *vbar) == true)
            {
                
//9
                solvable_boxes->push(*pbar);
                cout<<"---- push "<<*pbar<<" to solvable queue."<<endl;
                cout<<"-------- Now : "<<boxes_area(solvable_boxes)*100/total_area<<"% solvable , ";
                cout<<boxes_area(unsolvable_boxes)*100/total_area<<"% unsolvable"<<endl;
                out<<"---- push "<<*pbar<<" to solvable queue."<<endl;
                out<<"-------- Now : "<<boxes_area(solvable_boxes)*100/total_area<<"% solvable , ";
                out<<boxes_area(unsolvable_boxes)*100/total_area<<"% unsolvable"<<endl;
//10
                flag = true;
                
//11
                delete vbar;
                break;
            }
//12
            if(system.Test2(*pbar, *vbar) == true )
            {
//13
                if(Svar.size()==0)
                {
//14
                    unsolvable_boxes->push(*pbar);
                    cout<<"---- push "<<*pbar<<" to unsolvable queue."<<endl;
                    cout<<"-------- Now : "<<boxes_area(solvable_boxes)*100/total_area<<"% solvable , ";
                    cout<<boxes_area(unsolvable_boxes)*100/total_area<<"% unsolvable"<<endl;
                    out<<"---- push "<<*pbar<<" to unsolvable queue."<<endl;
                    out<<"-------- Now : "<<boxes_area(solvable_boxes)*100/total_area<<"% solvable , ";
                    out<<boxes_area(unsolvable_boxes)*100/total_area<<"% unsolvable"<<endl;
//15
                    flag = true;
//16
                    delete vbar;
                    break;
                }
            }
//17
            else
            {
//18
                if(vbar->Split(0)==true)
                {
      //              cout<<"Var::   Split "<<*vbar<<endl;
                    for(i=0;i<4;i++)
                    {
                        Svar.push(*(vbar->pChildren[i]));
                    }
                }
                delete vbar;
            }
        }
//19
        if( flag == false )
        {
//20
            if(pbar->Split(0)==true)
            {
                cout<<"Para::   Split "<<*pbar<<endl;
                for(i=0;i<4;i++)
                {
                    Ppara.push(*(pbar->pChildren[i]));
                }
            }
        }
        delete pbar;
    }
    out.close();
}
template <class NT>
void Output_area(BoxT<NT> * para_box, queue<BoxT<NT>> * solvable_boxes, queue<BoxT<NT>> * unsolvable_boxes )
{
    
    NT total_area=box_area(*para_box);
    cout<<endl<<"   &&&&&  Result  &&&&&   "<<endl;
    cout<<" / "<<endl;
    cout<<"| sovlable boxes total: "<<boxes_area(solvable_boxes)*100/total_area<<endl;
    cout<<"| unsolvable boxes total : "<<boxes_area(unsolvable_boxes)*100/total_area<<endl;
    cout<<" \\ "<<endl;
    cout<<"   &&&&&  Result  &&&&&   "<<endl;
}
#endif /* srouce_h */
