CXX = g++
CXXFLAGS = -Wall

proj2: main.cpp Race.o Track.o Player.o
	$(CXX) $(CXXFLAGS) main.cpp Race.o Track.o Player.o -o proj2

Race.o: Race.h Race.cpp Track.o Player.o
	$(CXX) $(CXXFLAGS) -c Race.cpp

Track.o: Track.h Track.cpp
	$(CXX) $(CXXFLAGS) -c Track.cpp

Player.o: Player.h Player.cpp
	$(CXX) $(CXXFLAGS) -c Player.cpp

clean:
	rm *~

run:
	./proj2
