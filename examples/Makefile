# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =
SRCS =  gradient.cpp  bmplib.cpp
OBJ = $(SRCS:.cpp=.o)


all: gradient

gradient: $(OBJ)
	$(CC) $(CFLAGS) -o gradient $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o lab5 *~

