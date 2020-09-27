SRC = $(wildcard *.cpp *.h)

example1: $(SRC)
	g++ example1.cpp -o example1 --std=c++14
