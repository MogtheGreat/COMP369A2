CPP = gcc
OFLAG = -o
CPPFLAGS = -Wall
LIBFLAGS = `pkg-config --cflags --libs allegro` -lstdc++
.SUFFIXES : .o .cpp .c
.cpp.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<
.c.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<

PunkEscape: main.o
	$(CPP) $(CPPFLAGS) main.o $(LIBFLAGS) $(OFLAG) PunkEscape

main.o: main.cpp

clean:
	rm -f *.o PunkEscape