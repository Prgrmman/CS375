CC=g++ -g -std=c++11
all: shortest

test: all
	./shortest
shortest: shortest.cpp Matrix.o
	$(CC) shortest.cpp Matrix.o -o shortest
Matrix.o: Matrix.cpp Matrix.h
	$(CC) -c Matrix.cpp -o Matrix.o

clean:
	rm shortest *.o
