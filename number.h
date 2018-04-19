// This is a widget which displays a large number on the screen.
// The valid numbers are between 0-9.  
// $Revision: 1.1 $
//   $Log: number.h,v $
//   Revision 1.1  2017/04/17 18:01:52  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
#ifndef NUMBER_H
#define NUMBER_H
#include "widget.h"
class Number: public Widget
{
public:
    Number(int x, int y);
    Number();
    
    //widget functions
    virtual void handleEvent(Event *e);
    virtual void display();
    
    //number functions
    void val(int n);
    int val();
private:
    unsigned short int n;  //the number itself
};

#endif