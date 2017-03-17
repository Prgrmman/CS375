CC= g++ -std=c++11

all: semest linear

semest: semest.cpp
	$(CC) semest.cpp -o semest

linear: linear.cpp Matrix.h
	$(CC) linear.cpp -o linear

submit:
	tar -zcvf terner_cpp_used.tar.gz semest.cpp linear.cpp Matrix.h readme.doc makefile

clean:
	-rm semest linear
