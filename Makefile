all: StrList
 
StrList: main.o StrList.o
	gcc -Wall -g -o StrList StrList.o main.o 

StrList.o: StrList.h
main.o: StrList.h


clean:
	rm -f *.o StrList
