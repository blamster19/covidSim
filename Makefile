#CPPFLAGS=-I/usr/include/python3.6m -lpython3.6m
CPPFLAGS=-Wall
TARGET=covidSim
OBJS=obj/main.o obj/city.o obj/person.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o bin/$@ $(OBJS) $(CPPFLAGS)

obj/main.o: src/main.cpp src/city.hpp
	$(CXX) -c src/main.cpp -o $@

obj/city.o: src/city.cpp src/city.hpp src/person.cpp src/person.hpp
	$(CXX) -c src/city.cpp -o $@

obj/person.o: src/person.cpp src/person.hpp
	$(CXX) -c src/person.cpp -o $@
