# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall

all: ListInt_test

ListInt_test: ListInt.o ListInt_test.o
	g++ -g -Wall -o ListInt_test ListInt.o ListInt_test.o

# example using MAKE variables $(CC) is replaced with g++, etc.
ListInt.o: ListInt.h ListInt.cpp
	$(CC) $(CFLAGS) -c ListInt.cpp

ListInt_test.o: ListInt.h ListInt_test.cpp
	$(CC) $(CFLAGS) -c ListInt_test.cpp

clean:
	rm -f *.o ListInt_test *~

tarit:
	tar cvf ListInt.tar ListInt.h ListInt.cpp ListInt_test.cpp Makefile
	scp ListInt.tar redekopp@ee.usc.edu:Sites/cs103
