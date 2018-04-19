//Just a simple display of a dot in big number style
//$Revision: 1.1 $
//  $Log: dot.h,v $
//  Revision 1.1  2017/04/19 01:58:02  1ea49c2b19284e86b645075d033e28d0
//  *** empty log message ***
//
#ifndef Dot_H
#define Dot_H
#include "widget.h"

class Dot : public Widget 
{
public:
    Dot(int _x, int _y);
    Dot();
    
    virtual void display();
    virtual void handleEvent(Event *e);
};

#endif
