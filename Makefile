CC=g++
CXXFLAGS=-g
LDFLAGS=-pthread
WIDGET=term.o application.o keystream.o widget.o
TARGETS=numberTest stopwatch

all: $(TARGETS)
numberTest: $(WIDGET) number.o numberTest.o timer.o
stopwatch: $(WIDGET) stopwatch.o clockDisplay.o number.o timer.o dot.o
clean:
	rm -f $(TARGETS) *.o
