// This is a widget which displays a large number on the screen.
// The valid numbers are between 0-9.  
// $Revision: 1.1 $
//   $Log: number.cpp,v $
//   Revision 1.1  2017/04/17 18:01:52  1ea49c2b19284e86b645075d033e28d0
//   Initial revision
//
#include <iostream>
#include "term.h"
#include "number.h"

using namespace std;

static const char nums[10][5][6] = {
  {   "#####",
      "#   #",
      "#   #",
      "#   #",
      "#####" },

  {    "  #  ",
       "  #  ",
       "  #  ",
       "  #  ",
       "  #  "},

  {   "#####",
      "    #",
      "#####",
      "#    ",
      "#####"},

  {   "#####",
      "    #",
      "#####",
      "    #",
      "#####"},

  {    "#   #",
       "#   #",
       "#####",
       "    #",
       "    #" },

  {    "#####",
       "#    ",
       "#####",
       "    #",
       "#####"},

  {   "#####",
      "#    ",
      "#####",
      "#   #",
      "#####"},

  {   "#####",
      "    #",
      "    #",
      "    #",
      "    #"},

  {   "#####",
      "#   #",
      "#####",
      "#   #",
      "#####"},

  {   "#####",
      "#   #",
      "#####",
      "    #",
      "    #"}
};    



Number::Number(int _x, int _y) : Widget(_x, _y, 5, 5), n(0)
{
    //nothing to do here
}


Number::Number() : Number(1, 1)
{
    //nothing to do here
}

    
//widget functions
void 
Number::handleEvent(Event *e)
{
    //ignore the event  pretty easy, eh?
}


void 
Number::display()
{
    //for every row in the number
    for(int i=0; i<5; i++) {
        cout << cursorPosition(x(), y()+i);
        //for each character
        for(int j=0; j<5; j++) {
            //  if character is a # display white block
            if(nums[n][i][j] == '#')  {
                cout << reverseVideo << ' ';
            } else  {
                //  otherwise, display an empty space
                cout << normal << ' ';
            }
        }
    }
    cout << normal;

    cout.flush();
}
   

//number functions
void 
Number::val(int n)
{
    this->n = n%10;
}


int 
Number::val()
{
    return n;
}