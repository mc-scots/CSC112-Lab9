//This creates a display for the stopwatch.
//The display is in the format MM:SS:HH for Minutes, seconds, and hundredths of seconds
//$Revision: 1.1 $
//  $Log: clockDisplay.h,v $
//  Revision 1.1  2017/04/19 01:58:02  1ea49c2b19284e86b645075d033e28d0
//  *** empty log message ***
//
#ifndef CLOCKDISPLAY_H
#define CLOCKDISPLAY_H
#include <vector>
#include "widget.h"
#include "dot.h"
#include "number.h"

class ClockDisplay : public Widget
{
public:
    ClockDisplay(int _x, int _y);
    ClockDisplay();
    
    virtual void display();
    virtual void handleEvent(Event *e);

private:
    std::vector<Number*> numbers;
    Dot *c1;
    Dot *c2;
};

#endif