CXX= g++
CXXFLAGS= -g -Wall -std=gnu++11

all: dpda.exe

dpda.exe: dpda.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.exe *.o
