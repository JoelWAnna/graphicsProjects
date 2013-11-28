CC=g++
CFLAGS=-c -std=c++0x -Wall
LDFLAGS=-lXext -L/usr/local/lib -lfltk_gl -lfltk -lpthread -lm -lX11 -ldl -lGL -lglut -lGLU 
SOURCES=CubicBspline.cpp GenericException.cpp Objects.cpp Tree.cpp World.cpp FerrisWheel.cpp Ground.cpp Track.cpp Wall.cpp WorldWindow.cpp libtarga.c
OBJECTS=$(SOURCES:.cpp=.o)
EXE=p2
All: $(SOURCES) $(EXE)
	
clean: rm *.o
$(EXE): $(OBJECTS)
	$(CC) -std=c++0x -o $@ $(OBJECTS) $(LDFLAGS) 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

all: objects full
	
objects: CubicBspline.cpp GenericException.cpp Objects.cpp Tree.cpp World.cpp FerrisWheel.cpp Ground.cpp Track.cpp Wall.cpp WorldWindow.cpp libtarga.c
	g++ -c -std=c++0x *.cpp *.c
full: CubicBspline.o GenericException.o Objects.o Tree.o World.o FerrisWheel.o Ground.o Track.o Wall.o WorldWindow.o
	g++ -std=c++0x -o p2 *.o -lfltk_gl -lGLU -lGL -lfltk -lXext -lpthread -ldl -lm -lX11 -L/usr/local/lib -lfltk_gl -lfltk -lpthread -ldl -lm -lX11 -ldl -lX11 -lGL -lglut -lfltk -lfltk_images -lGLU 


