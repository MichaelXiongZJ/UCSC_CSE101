CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = bard.o bard_util.o

bard: $(OBJECTS)
		$(CXX) -g $(CXXFLAGS) -o $@ bard.o bard_util.o

bard.o: bard.cpp bard_util.h bard_util.cpp
		$(CXX) -g $(CXXFLAGS) -c bard.cpp

bard_util.o: bard_util.cpp bard_util.h
		$(CXX) -g $(CXXFLAGS) -c bard_util.cpp

clean:
	rm *.o
	rm bard
