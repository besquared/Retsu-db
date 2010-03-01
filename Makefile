CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -I/usr/local/include -I.
LIBS := -L/usr/local/lib -L./lib -ltokyocabinet -lretsu -lv8 -lboost_filesystem-xgcc40-mt -lboost_system-xgcc40-mt
OBJECTS := Dimension.o Dimensions.o Measure.o Measures.o Record.o RIDList.o Table.o 

build/main: lib/libretsu.a Commander.o main.o
	$(CXX) $(INCLUDES) $(LIBS) $(CXXFLAGS) main.o Commander.o -o build/main

main.o: main.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c main.cpp

Commander.o: source/Commander.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c source/Commander.cpp

lib/libretsu.a: $(OBJECTS)
	ar cr lib/libretsu.a $(OBJECTS) && rm *.o

%.o: source/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

clean:
	\rm -f *.o
	\rm -f lib/libretsu.a
	\rm -f build/main
	\rm -rf build/main.dSYM