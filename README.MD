## Introduction

In today's lab we will be write a little stopwatch program. The display
of this program uses my custom number widget to display great big
numbers in the terminal. The end result is a program that looks like
this:

![Stopwatch.png](Stopwatch.png "Stopwatch.png")

Like a normal stop watch, this displays minutes, seconds, and hundredths
of a second. We will also be making use of a nifty OOP threaded timer
which I wrote. In fact, most of this code has already been written for
you, you just have to read it and prove that you understand it by
piecing together a complete application.

So let's dive in\!

## Number Test

Your first stop is the number test program. Go ahead and run make and
then run ./numberTest. This will display a single number on the screen.
You can control this application as follows:

  - Press Enter to start/stop the timer which will make the number
    count.
  - Press ESC to exit.

Go ahead and play with the application, and then read numberTest.cpp to
see how it works. This should give you many powerful clues about how to
make the stopwatch work. Be sure to take a glance at the timer.h and
timer.cpp files while you are at it\!

## The Stopwatch

Now that you fully understand the sample code, you're ready to write the
stopwatch\! You'll want to make ClockDisplay respond to the time event
by incrementing the display. Handle the keyboard events in the same way
that they are handled in Number Test.

You will need to put the timer somewhere. Pick your place carefully\!
(But putting it inside ClockDisplay would be a pretty good idea.)

Really, the biggest challenge in this one is getting the clock display
to work correctly. It's not too bad though, a handful of if statements
and you're there.

Enjoy\!
