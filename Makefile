CC = mpic++
CFLAGS = -c -O2
HOME =
INCLUDE =
LDFLAGS=-L/usr/X11R6/lib
LIBS=-lm -lpthread -lX11

SOURCES=Camera.cpp Color.cpp Light.cpp main.cpp Ray.cpp Scene.cpp Sphere.cpp Tracing.cpp Vector.cpp Plane.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INCLUDE) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
clean:
	rm -rf *.o $(EXECUTABLE)
