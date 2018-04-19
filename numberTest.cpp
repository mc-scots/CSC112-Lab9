#include <iostream>
#include <unistd.h>
#include "widget.h"
#include "number.h"
#include "term.h"
#include "application.h"
#include "timer.h"

using namespace std;

class NumberTester : public Widget
{
public:
    NumberTester() 
    {
        n = new Number();
        t = new Timer(0.5);
        t->receiver(this);
    }
    
    
    virtual void display()
    {
        n->display();
    }
    
    
    virtual void handleEvent(Event *e) 
    {
        if(e->type()=="keyboard") {
            KeyboardEvent *kb = (KeyboardEvent *)e;
            
            //start and stop timer
            if(kb->key() == ENTER) {
                if(t->running()) {
                    t->stop();
                } else {
                    t->start();
                }
            }
            
            //exit on esc
            if(kb->key() == ESC) {
                t->stop();
                ((Application*) parent())->running(false);
            }
        } else if(e->type() == "tick") {
            //increment and redisplay the number
            n->val(n->val()+1);
            display();
        }
    }
private:
    Number *n;
    Timer  *t;
};

int main()
{
    Application *app = new Application;
    app->child(new NumberTester());
    
    cout << clearScreen << cursorOff;
    
    app->eventLoop();
    
    cout << clearScreen << cursorOn;
    return 0;
}