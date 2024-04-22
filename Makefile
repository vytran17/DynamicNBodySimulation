CC = g++
# CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -I./boost/include
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
# TEST_LIBS = -lboost_unit_test_framework
TEST_LIBS = -L./boost/lib -lboost_unit_test_framework
DEPS = CelestialBody.hpp Universe.hpp 
OBJECTS = CelestialBody.o Universe.o
PROGRAM = NBody
STATIC_LIB = NBody.a
TEST = test

.PHONY: all clean lint

all: $(PROGRAM) $(STATIC_LIB) $(TEST)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(TEST_LIBS)

$(STATIC_LIB): $(OBJECTS)
	ar rcs $(STATIC_LIB) $(OBJECTS)

clean:
	rm *.o $(PROGRAM) $(STATIC_LIB) $(TEST)

lint:
	cpplint *.cpp *.hpp
