SRC = $(wildcard *.cpp *.h)

all: test_main

example1-basic.o: $(SRC)
	g++ example1-basic.cpp -c -o example1-basic.o --std=c++17 -g

example2-mocks.o: $(SRC)
	g++ example2-mocks.cpp -c -o example2-mocks.o --std=c++17 -g

example3-inline.o: $(SRC)
	g++ example3-inline.cpp -c -o example3-inline.o --std=c++17 -g
	
test_main: example1-basic.o example2-mocks.o test_main.cpp
	g++ example1-basic.o example2-mocks.o test_main.cpp -o test_main --std=c++17 -g

inline_test:
	g++ example3-inline.o -o test_inline --std=c++17 -g

clean:
	rm -f example1-basic.o example2-mocks.o test_main
