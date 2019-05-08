CFLAGS = -c -O2
UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	INCLUDE=-I/opt/X11/include
	LDFLAGS=-L/usr/X11/lib
	LIBS=-lm -lpthread -lX11
endif
ifeq ($(UNAME_S), Linux)
	LDFLAGS=-L/usr/X11/lib
	LIBS=-lm -lpthread -lX11
endif

SOURCES=Camera.cpp Color.cpp Light.cpp main.cpp Ray.cpp Scene.cpp Sphere.cpp Tracing.cpp Vector.cpp Plane.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(INCLUDE) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
