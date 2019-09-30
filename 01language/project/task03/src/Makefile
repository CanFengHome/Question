all:
	gcc -Wall -g -std=c99 -I../include -fpic -c add.c -o ../obj/add.o
	gcc -Wall -g -std=c99 -I../include -fpic -c sub.c -o ../obj/sub.o
	gcc -shared ../obj/*.o -o ../lib/libmycal.so
	
clean:
	rm -rf ../lib/* ../obj/*
