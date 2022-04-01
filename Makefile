CPPFLAGS=-Wall -I/usr/include/python3.9 -lpython3.9
TARGET=covidSim
OBJS=obj/main.o obj/city.o obj/person.o obj/generator.o obj/Plotter.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o bin/$@ $(OBJS) $(CPPFLAGS)

obj/main.o: src/main.cpp src/city.hpp
	$(CXX) -c src/main.cpp -o $@

obj/city.o: src/city.cpp src/city.hpp src/person.cpp src/person.hpp
	$(CXX) -c src/city.cpp -o $@

obj/person.o: src/person.cpp src/person.hpp
	$(CXX) -c src/person.cpp -o $@

obj/generator.o: src/generator.cpp src/generator.hpp
	$(CXX) -c src/generator.cpp -o $@

obj/Plotter.o: deps/Plotter.cpp deps/Plotter.h
	$(CXX) -c deps/Plotter.cpp -o $@ $(CPPFLAGS)
