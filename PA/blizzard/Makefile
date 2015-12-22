# Name: Aaron Cheney
# email: aaron.logan.cheney@gmail.com

CXX = g++
CPPFLAGS = -g -Wall

all: social_network
	./social_network users_large.txt

social_network: user.o network.o social_network.o social_network.cpp
	$(CXX) $(CPPFLAGS) user.o network.o social_network.o -o social_network

user.o: user.h user.cpp
	$(CXX) $(CPPFLAGS) -c user.cpp -o user.o

network.o: network.h user.h network.cpp
	$(CXX) $(CPPFLAGS) -c network.cpp -o network.o

social_network.o: network.h user.h social_network.cpp
	$(CXX) $(CPPFLAGS) -c social_network.cpp -o social_network.o

.PHONY: clean
clean:
	rm -f social_network *.o
