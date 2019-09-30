all:
	gcc -Wall -g -std=c99 -I../include main.c -o test.out -L../lib -lmycal -Wl,-rpath ../lib
	gcc -Wall -g -std=c99 test_dlopen.c -o test_dlopen.out
clean:
	rm -rf *.out