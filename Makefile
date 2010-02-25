CXX = g++
CXXFLAGS = -Wall -g

libretsu: build/domain/data/dimension.o build/domain/data/measure.o build/domain/data/record.o build/domain/data/RIDList.o
	$(CXX)

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp