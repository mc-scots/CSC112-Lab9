# Lab 9 - Pong
In this lab, we are going to complete the code we started in class.  
This will be a grand adventure that will test how much you truly
understand about object oriented code, so let's dive in!

## The Paddle
Let's make the paddle.  We'll start off by designing it in paddle.h.
Of course, this will have a position on the screen, as well as a 
velocity (we'll move it not by rapid fire keypress, but by selecting
velocities from the user).

So if we design this, it may come out looking something like this:

### paddle.h
```c++
///////////////////////////////////////////////////////////////////////////
// File: paddle.h
// Purpose: Class definition of a representation of a paddle
///////////////////////////////////////////////////////////////////////////
#include <Fl/fl_draw.H>
#ifndef PADDLE_H
#define PADDLE_H
class Paddle
{
public:
    /////////////////////////
    // Constructors / Destructors
    /////////////////////////
    Paddle();  
    Paddle(int _x, int _y, int _width, int _height, int _vx, int _vy, Fl_Color _color);
    Paddle(const Paddle &other);
    virtual ~Paddle();

    /////////////////////////
    // Accessors and mutators
    /////////////////////////
    virtual void x(int _x);
    virtual int x() const;

    virtual void y(int _y);
    virtual int y() const;

    virtual void size(int _size);
    virtual int size() const;

    virtual void vx(int _vx);
    virtual int vx() const;

    virtual void vy(int _vy);
    virtual int vy() const;

    virtual void color(Fl_Color _color);
    virtual Fl_Color color() const;

    /////////////////////////
    // Paddle Methods
    /////////////////////////

    // Update the paddle for the next frame
    virtual void move();

    // Draw the paddle during an FLTK draw context
    virtual void draw(int xoffset, int yoffset);

private:
    int _x;  //x coordinate of the paddle
    int _y;  //y coordinate of the paddle
    int _width;  //width of the paddle
    int _height; //height of the paddle
    int _vx; //x velocity
    int _vy; //y velocity
    Fl_Color _color;  //color of the paddle
};
#endif
```

Does this pass the OOP smell test?  It should not!  Why?  Well, this
makes the paddle pretty much identical to ball.  Both the ball and the
paddle are physical objects that will behave like solid objects in our
pong world.  So they should really both be children of some super
class.  Let's fix that!

## Physical Objects
We are going to create a physical object which has the following
properties:

* It has position.
* It has velocity.
* It has the ability to update position based on its velocity.
* It has a pure virtual draw function.
* It can detect collisions with other physical objects.

With all these in mind, here is my physical object design.  Go ahead
and create physical.h

### physical.h
```c++
///////////////////////////////////////////////////////////////////////////
// File: physical.h
// Purpose: Class definition of a physical object
///////////////////////////////////////////////////////////////////////////
#include <Fl/fl_draw.H>
#ifndef PHYSICAL_H
#define PHYSICAL_H
class Physical_Object
{
public:
    /////////////////////////
    // Constructors
    /////////////////////////
    Physical_Object(int _x, int _y, int _w, int _h, int _vx, int _vy);
    Physical_Object(const Physical_Object &other);


    /////////////////////////
    // Accessor and Mutators
    /////////////////////////
    virtual void x(int _x);
    virtual int x() const;

    virtual void y(int _y);
    virtual int y() const;

    virtual void w(int _w);
    virtual int w() const;

    virtual void h(int _h);
    virtual int h() const;

    virtual void vx(int _vx);
    virtual int vx() const;

    virtual void vy(int _vy);
    virtual int vy() const;

    /////////////////////////
    // Physical Methods
    /////////////////////////
    // Update the object for the next frame
    virtual void move();

    // Draw the object during an FLTK draw context (Pure Virtual)
    virtual void draw(int xoffset, int yoffset)=0;

    // Check for collisions with another physical object
    virtual bool collides(const Physical_Object &other);

private:
    int _x;  //x coordinate of the physical object
    int _y;  //y coordinate of the physical object
    int _w;  //width of the physical object
    int _h; //height of the physical object
    int _vx; //x velocity
    int _vy; //y velocity
};

#endif
```

Having created this file, let's go on to constructing the
implementation file.

### physical.cpp
First, let's start off implementing the constructors.  These will be
fairly straightforward.
```cpp
/////////////////////////
// Constructors
/////////////////////////
Physical_Object::Physical_Object(int _x, int _y, 
                                 int _w, int _h, 
                                 int _vx, int _vy)
{
   //set all the fields using mutators
   x(_x);
   y(_y);
   w(_w);
   h(_h);
   vx(_vx);
   vy(_vy);
}

Physical_Object::Physical_Object(const Physical_Object &other)
{
   //set all the fields using mutators
   x(other.x());
   y(other.y());
   w(other.w());
   h(other.h());
   vx(other.vx());
   vy(other.vy());
}
```

Next up, let's add the accessors and mutators.  These will basically
be what was in Ball originally:

```c++
/////////////////////////
// Accessor and Mutators
/////////////////////////
void
Physical_Object::x(int _x)
{
    this->_x=_x;
}



int
Physical_Object::x() const 
{
    return this->_x;
}



void
Physical_Object::y(int _y)
{
    this->_y=_y;
}



int
Physical_Object::y() const 
{
    return this->_y;
}



void
Physical_Object::w(int _w)
{
    this->_w=_w;
}



int
Physical_Object::w() const 
{
    return this->_w;
}



void
Physical_Object::h(int _h)
{
    this->_h=_h;
}



int
Physical_Object::h() const 
{
    return this->_h;
}



void
Physical_Object::vx(int _vx)
{
    this->_vx=_vx;
}



int
Physical_Object::vx() const 
{
    return this->_vx;
}



void
Physical_Object::vy(int _vy)
{
    this->_vy=_vy;
}



int
Physical_Object::vy() const 
{
    return this->_vy;
}
```

And now, on to the object's methods.  We start with move, which we
steal from Ball

```c++
/////////////////////////
// Physical Methods
/////////////////////////

// Update the object for the next frame
void 
Physical_Object::move()
{
    //move the object by vx and vy
    x(x()+vx());
    y(y()+vy());
}
```

Now, on to collision detection!  I could have made you work this out
for yourself, but then I decided to show you how to do Axis Aligned
Bounding Box collisions.

```c++
// Check for collisions with another physical object
bool 
Physical_Object::collides(const Physical_Object &other)
{
    //behold the glories of axis aligned bounding box collision
    //detection!
    return x() < other.x() + other.w()&&
           x() + w() > other.x() &&
           y() < other.y() + other.h() &&
           y() + other.h() > other.y();
}
```

Now, we could could add color to this, but I decided to leave that in
Ball and Paddle.  The idea is that this makes Physical_Object more
generic so you can use it in your own games. (You're welcome!)

## Refactoring the Paddle
So now, we need to adapt Paddle so that it will be a subclass of
Physical_Object.  This process is called refactoring, and willingness
to do this is one of the many things that separates elite programmers
from mere code grunts.

### paddle.h
First, let's change paddle.h
```c++
///////////////////////////////////////////////////////////////////////////
// File: paddle.h
// Purpose: Class definition of a representation of a paddle
///////////////////////////////////////////////////////////////////////////
#include <Fl/fl_draw.H>
#include "physical.h"
#ifndef PADDLE_H
#define PADDLE_H
class Paddle : public Physical_Object
{
public:
    /////////////////////////
    // Constructors / Destructors
    /////////////////////////
    Paddle();  
    Paddle(int _x, int _y, int _w, int _h, int _vx, int _vy, Fl_Color _color);
    Paddle(const Paddle &other);
    virtual ~Paddle();

    /////////////////////////
    // Accessors and mutators
    /////////////////////////
    virtual void color(Fl_Color _color);
    virtual Fl_Color color() const;

    /////////////////////////
    // Paddle Methods
    /////////////////////////
    // Draw the paddle during an FLTK draw context
    virtual void draw(int xoffset, int yoffset);

private:
    Fl_Color _color;  //color of the paddle
};
#endif
```

### paddle.cpp
Now, let's implement the paddle!

```c++
//////////////////////////////////////////////////////////////////////////
// Implementation of the pong paddle
///////////////////////////////////////////////////////////////////////////
#include "paddle.h"

/////////////////////////
// Constructors / Destructors
/////////////////////////
Paddle::Paddle() : Paddle(0, 0, 30, 100, 0, 0, FL_RED)
{
    //nothing to do
}


Paddle::Paddle(int _x, int _y, int _w, int _h, int _vx, int _vy, Fl_Color _color) : Physical_Object(_x,_y,_w,_h,_vx,_vy)
{
    color(_color);
}


Paddle::Paddle(const Paddle &other) : Physical_Object(other)
{
    color(other.color());
}


Paddle::~Paddle()
{
    //nothing to do
}

/////////////////////////
// Accessors and mutators
/////////////////////////
void 
Paddle::color(Fl_Color _color)
{
    this->_color = _color;
}

Fl_Color 
Paddle::color() const
{
    return _color;
}

/////////////////////////
// Paddle Methods
/////////////////////////
// Draw the paddle during an FLTK draw context
void 
Paddle::draw(int xoffset, int yoffset)
{
    //draw the circle
    fl_color(_color);
    fl_rectf(xoffset+x(), yoffset+y(), w(), h());
}
```

## Refactor Ball
Now it's your turn!  Give Ball the same treatment.  When you are done,
Ball should be a subclass of Physical_Object and have no more than the
necessary functions.  (You will be graded on your refactoring.)


## Add the Paddles to the play field
Now, let's add the paddles to our play field.  First, we need to modify
field.h.  Of course, we need to add our include file:

```c++
#include "paddle.h"
```

We also need to add some private variables:

```c++
    Paddle _player;
    Paddle _computer;
```

Next, we need to add the paddles to our reset_ball method.  Place the
paddle position after the ball positioning.  These additions are:
```c++
   //position the paddles
   _player.w(_ball.size());
   _player.h(h()/4);
   _computer.w(_player.w());
   _computer.h(_player.h());
   _player.x(0);
   _player.y(h()/2-_player.h()/2);
   _computer.x(w()-_computer.w());
   _computer.y(_player.y());
```

Then we need to draw the paddles in the field draw method:
```c++
    _player.draw(x(), y());
    _computer.draw(x(), y());
```

Finally, let's add these things into the make file.  Add paddle.o and
physical.o to the pong target's dependencies list. Make and run the
program, once it runs you should see two stationary paddles and
a moving ball.

## Player Input
Now, let's turn our attention to player input.  We want the player to
move their paddle up and down using the arrow keys.  To do this, we
need to handle the KEYBOARD and KEYUP events.  However, in order to
capture keyboard events, we have to first respond to focus and unfocus
events.  Add the following to the switch statement in the event
handler:

```c++
    case FL_FOCUS:
    case FL_UNFOCUS:
        return 1;
        break;
```

Now that we can play with the keyboard, let's handle the events.  When
the user presses up, we set vy to -10.  When they press down, vy is
set to 10. When they release an arrow, the paddle stops.  This is all
handled via the following:
```c++
    case FL_KEYBOARD:
        switch(Fl::event_key()) {
        case FL_Up:
            _player.vy(-10);
            break;
        case FL_Down:
            _player.vy(10);
            break;
        }
        return 1;
        break;
    case FL_KEYUP:
        switch(Fl::event_key()) {
        case FL_Up:
        case FL_Down:
            _player.vy(0);
        }
        return 1;
        break;
```

Go ahead and compile and see if you can move your paddle.

What?  You can't?  Of course not! Add the following to the end of your
update function in field:
```c++
    _player.move();
```

## Paddle Collision Detection
Now we move on to collision detection with the paddles.  To do this,
we make a copy of the ball, move it, and then check collision.  If it
collides with a paddle, we reverse the ball's direction.  This is all
done in the update method after the pause but before the edge
collision detection:
```c++
    //try the move, check for paddle collisions
    Ball trial = _ball;
    trial.move();
    if(trial.collides(_player) or trial.collides(_computer)) {
        _ball.vx(-_ball.vx());
    }
```

After the line with _ball.move(), we let the computer make a move.
Let's make it unbeatable for now!

```c++
    //the computer is a dirty cheat!  Improve upon this!
    _computer.y(_ball.y());
    _computer.move();
```

If you compile and run this, you will have a game that works, but it
is not winnable.

## Challenges for you
Now, to round this out, let's modify the game and make it your own.  
1. Make the computer beatable, but competent.
2. Make the paddle change the trajectory of the ball.  The original
   pong factored in the vertical velocity of the ball as well as where
   it struck the paddle.
3. Keep score and display it somewhere.

After you have completed these three challenges, you will have written
your first video game.  Congratulations!
