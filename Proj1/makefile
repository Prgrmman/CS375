all: keys

keys: keys.c
	gcc  -g keys.c -o keys
test: all
	./keys

submit:
	tar -cvzf jonathan_terner_c_used.tar.gz keys.c makefile inputFile.txt testTwo.txt readme.rtf
debug: all
	gdb ./keys
clean:
	-rm keys 
