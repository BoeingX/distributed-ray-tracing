SETUP = sallesinfo# possibilities: sallesinfo, arch, windows
CC = mpic++
CFLAGS = -c -O2
ifeq ($(SETUP),sallesinfo)
	## salles informatiques @X
	INCLUDE = -I/usr/local/CImg-1.6.2/
	LIBS = -lpthread -lX11
	LDPATH = 
endif
ifeq ($(SETUP),arch)
	HOME =
	INCLUDE =
	LDFLAGS=-L/usr/X11R6/lib
	LIBS=-lm -lpthread -lX11
endif

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
