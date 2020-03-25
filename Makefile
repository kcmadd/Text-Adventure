output: adventure.o item.o stack.o keyword.o room.o
	gcc adventure.o item.o stack.o keyword.o room.o -o output

adventure.o: adventure.c
	gcc -c adventure.c

item.o: item.c item.h
	gcc -c item.c

stack.o: stack.c stack.h
	gcc -c stack.c

keyword.o: keyword.c keyword.h
	gcc -c keyword.c

room.o: room.c room.h
	gcc -c room.c
clean:
	rm *.o output