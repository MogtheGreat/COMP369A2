CPP = gcc
OFLAG = -o
CPPFLAGS = -Wall
LIBFLAGS = `pkg-config --cflags --libs allegro` -lstdc++
.SUFFIXES : .o .cpp .c
.cpp.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<
.c.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<

PunkEscape: main.o graphics.o movement.o auxi.o enemy.o
	$(CPP) $(CPPFLAGS) main.o graphics.o movement.o auxi.o enemy.o $(LIBFLAGS) $(OFLAG) PunkEscape

main.o: main.cpp

graphics.o: graphics.cpp graphics.h

movement.o: movement.cpp movement.h

auxi.o: auxi.cpp auxi.h

enemy.o:  enemy.h enemy.cpp

clean:
	rm -f *.o PunkEscape