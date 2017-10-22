OBJS	= main.o funcs.o graph.o hashtable.o nnode.o
SOURCE	= main.cpp funcs.cpp graph.cpp hashtable.cpp nnode.cpp
HEADER 	= funcs.h graph.h hashtable.h nnode.h
OUT	= elegxos
CC	= g++
FLAGS	= -g -c

all:	$(OBJS)
		$(CC) -g $(OBJS) -o $(OUT) 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

funcs.o: funcs.cpp
	$(CC) $(FLAGS) funcs.cpp
	
graph.o: graph.cpp
	$(CC) $(FLAGS) graph.cpp

hashtable.o: hashtable.cpp
	$(CC) $(FLAGS) hashtable.cpp

nnode.o: nnode.cpp
	$(CC) $(FLAGS) nnode.cpp
clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
