SRC = $(wildcard *.cpp *.h)

all: example1-basic example2-mocks

example1-basic: $(SRC)
	g++ example1-basic.cpp -o example1-basic --std=c++14 -g
	
example2-mocks: $(SRC)
	g++ example2-mocks.cpp -o example2-mocks --std=c++14 -g
   
clean:
	rm -f example1-basic example2-mocks
