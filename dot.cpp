#include "dot.h"
#include "term.h"

using namespace std;

Dot::Dot(int _x, int _y) : Widget(_x, _y, 2,5)
{
    //nothing to do here
}


Dot::Dot() : Dot(1,1)
{
    //nothing to do here
}
    
void 
Dot::display()
{
    cout << reverseVideo;
    cout << cursorPosition(x(),y()+3) << "  "
         << cursorPosition(x(),y()+4) << "  "
         << normal;
    
    cout.flush();
}



void 
Dot::handleEvent(Event *e)
{
    //ignore all events
}