CPP = gcc
OFLAG = -o
CPPFLAGS = -Wall
LIBFLAGS = `pkg-config --cflags --libs allegro` -lstdc++
.SUFFIXES : .o .cpp .c
.cpp.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<
.c.o:
	$(CPP) $(LIBFLAGS) $(CPPFLAGS) -c $<

PoliceEscape: main.o
	$(CPP) $(CPPFLAGS) main.o $(LIBFLAGS) $(OFLAG) PoliceEscape

main.o: main.cpp

clean:
	rm -f *.o PoliceEscape