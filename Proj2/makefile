CC= g++ -g -std=c++11 -Wall


dist: dist.cpp point.o timer.o
	$(CC) dist.cpp point.o timer.o -o dist

point.o: point.cpp point.h
	$(CC) -c point.cpp -o point.o

timer.o: timer.cpp timer.h
	$(CC) -c timer.cpp -o timer.o

submit: timer.cpp timer.h point.cpp point.h dist.cpp
	tar -czvf jonathan_terner_cpp_used.tar.gz timer.cpp timer.h point.cpp point.h dist.cpp makefile readme.doc
clean:
	-rm dist *.o
