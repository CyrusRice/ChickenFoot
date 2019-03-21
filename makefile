CXX = g++
CXXFLAGS = -Wall -g

project2: bone.o chickenyard.o player.o game.o field.o main.o
	$(CXX) $(CXXFLAGS) -o project2 bone.o chickenyard.o player.o  game.o field.o main.o

main.o: main.cpp game.h field.h player.h chickenyard.h bone.h
	$(CXX) $(CXXFLAGS) -c main.cpp

bone.o: bone.cpp bone.h
	$(CXX) $(CXXFLAGS) -c bone.cpp

chickenyard.o: chickenyard.cpp chickenyard.h bone.h
	$(CXX) $(CXXFLAGS) -c chickenyard.cpp

player.o: player.cpp player.h chickenyard.h bone.h
	$(CXX) $(CXXFLAGS) -c player.cpp

field.o: field.cpp field.h player.h chickenyard.h bone.h
	$(CXX) $(CXXFLAGS) -c field.cpp

game.o: game.cpp game.h field.h player.h chickenyard.h bone.h
	$(CXX) $(CXXFLAGS) -c game.cpp

clean:
	rm project2 *.o
