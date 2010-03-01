CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -I/usr/local/include -I.
LIBS := -L/usr/local/lib -L./lib -ltokyocabinet -lretsu -lv8 -lboost_filesystem-xgcc40-mt -lboost_system-xgcc40-mt
OBJECTS := Commander.o Dimension.o Dimensions.o Measure.o Measures.o Record.o RIDList.o Table.o 

build/main: lib/libretsu.a
	$(CXX) $(INCLUDES) $(LIBS) $(CXXFLAGS) -o build/main main.cpp

lib/libretsu.a: $(OBJECTS)
	ar cr lib/libretsu.a $(OBJECTS) && rm *.o

%.o: source/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

clean:
	\rm *.o
	\rm lib/libretsu.a
	\rm main