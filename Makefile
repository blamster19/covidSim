CPPFLAGS=-pedantic -Wall -Wextra -Werror -Weffc++ -Wunreachable-code -std=c++14
PYTHON= $(shell python3-config --includes --libs)
DEBUG=-g
TARGET=covidSim
OBJS=obj/main.o obj/city.o obj/person.o obj/generator.o obj/Plotter.o

$(shell mkdir -p obj bin plots)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(DEBUG) -o bin/$@ $(OBJS) $(CPPFLAGS) $(PYTHON)

obj/main.o: src/main.cpp src/city.hpp
	$(CXX) $(DEBUG) -c src/main.cpp -o $@ $(CPPFLAGS)

obj/city.o: src/city.cpp src/city.hpp src/person.cpp src/person.hpp
	$(CXX) $(DEBUG) -c src/city.cpp -o $@ $(CPPFLAGS)

obj/person.o: src/person.cpp src/person.hpp
	$(CXX) $(DEBUG) -c src/person.cpp -o $@ $(CPPFLAGS)

obj/generator.o: src/generator.cpp src/generator.hpp
	$(CXX) $(DEBUG) -c src/generator.cpp -o $@ $(CPPFLAGS)

obj/Plotter.o: deps/Plotter.cpp deps/Plotter.h
	$(CXX) $(DEBUG) -c deps/Plotter.cpp -o $@ $(PYTHON)
