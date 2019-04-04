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


