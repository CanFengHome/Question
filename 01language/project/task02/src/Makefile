all:
	gcc -Wall -g -std=c99 -I../include -static -c add.c -o ../obj/add.o
	gcc -Wall -g -std=c99 -I../include -static -c sub.c -o ../obj/sub.o
	ar -r ../lib/libmycal.a ../obj/*.o
clean:
	rm -rf ../lib/* ../obj/*