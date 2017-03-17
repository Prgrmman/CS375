CC=g++ -std=c++11

all: cluster citypath

run1: cluster
	./cluster input.txt

run2: citypath
	./citypath input2.txt

cluster: cluster.cpp Disjoint.o Node.hpp
	$(CC) cluster.cpp Disjoint.o -o cluster 
Disjoint.o: Disjoint.cpp Disjoint.hpp
	$(CC) -c Disjoint.cpp -o Disjoint.o

citypath: citypath.cpp Heap.o Graph.o Node.hpp
	$(CC) citypath.cpp Heap.o Graph.o -o citypath

Heap.o: Heap.cpp Heap.hpp Node.hpp
	$(CC) -c Heap.cpp -o Heap.o

Graph.o: Graph.cpp Graph.hpp
	$(CC) -c Graph.cpp -o Graph.o

submit:
	tar -cvzf Jonathan_Terner_cpp_used.tar.gz *
clean:
	@- rm *.o cluster citypath *.gz

