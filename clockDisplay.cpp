#include "clockDisplay.h"


ClockDisplay::ClockDisplay(int _x, int _y) : Widget(_x, _y, 1, 1)
{
    Widget *w;
    
    w = new Number(_x, _y);
    numbers.push_back((Number*) w);
    w = new Number(w->x() + w->width() + 1, _y);
    numbers.push_back((Number*) w);
    w = new Dot(w->x() + w->width() + 1, _y);
    c1 = (Dot *) w;
    w = new Number(w->x() + w->width() + 1, _y);
    numbers.push_back((Number*) w);
    w = new Number(w->x() + w->width() + 1, _y);
    numbers.push_back((Number*) w);
    w = new Dot(w->x() + w->width() + 1, _y);
    c2 = (Dot *) w;
    w = new Number(w->x() + w->width() + 1, _y);
    numbers.push_back((Number*) w);
    w = new Number(w->x() + w->width() + 1, _y);
    numbers.push_back((Number*) w);
    
    //calculate width and height
    width(numbers.back()->x() + numbers.back()->width() - _x);
    height(5);
}


ClockDisplay::ClockDisplay() : ClockDisplay(1, 1)
{
    
}


void 
ClockDisplay::display()
{
    //display the numbers
    for(auto itr = numbers.begin(); itr != numbers.end(); itr++) {
        (*itr)->display();
    }
    
    //display the separators
    c1->display();
    c2->display();
}


void 
ClockDisplay::handleEvent(Event *e)
{
    //your code here
    
    display();
}