#include <iostream>
#include "clockDisplay.h"
#include "term.h"
#include "application.h"
#include "timer.h"

using namespace std;

int main()
{
    Application *app = new Application();
    ClockDisplay *disp = new ClockDisplay();

    //set up the app and run it
    app->child(disp);
    app->eventLoop();
    
    return 0;
}
