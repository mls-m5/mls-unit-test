SRC = $(wildcard *.cpp *.h)

all: example1

example1: $(SRC)
	g++ example1.cpp -o example1 --std=c++14
   
clean:
	rm -f example1
