
CXX=gcc


all: main

main: 
	$(CXX) -c matrix.c 
	$(CXX) -c main.c
	$(CXX) -pthread  matrix.o main.o -o main
	@echo "use ./main -h"
clean:
	rm -f *.o main