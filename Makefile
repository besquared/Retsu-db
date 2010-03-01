CXX := g++
CXXFLAGS := -Wall -g
INCLUDES := -I/usr/local/include -I.
LIBS := -L/usr/local/lib -L.
OBJECTS := Commander.o Dimension.o Dimensions.o Measure.o Measures.o Record.o RIDList.o Table.o 

libretsu: $(OBJECTS)
	ar cr libretsu.a $(OBJECTS)

%.o: source/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $(inputs) -o $(output)