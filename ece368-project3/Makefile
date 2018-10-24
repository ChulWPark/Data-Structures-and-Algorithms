VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

all: dijkstra.o
	gcc -std=c99 -Werror -Wall -g -lm main.c dijkstra.o -o dijkstra

dijktra.o: main.c dijkstra.c dijkstra.h
	gcc -std=c99 -Werror -Wall -g -lm dijkstra.c dijkstra.h

test: all
	./dijkstra map6.txt query6.txt
	./dijkstra map5x5.txt query5x5.txt

sample:
	./shortestpath map6.txt query6.txt
	./shortestpath map5x5.txt query5x5.txt

sammem:
	$(VALG) ./shortestpath map6.txt query6.txt
	$(VALG) ./shortestpath map5x5.txt query5x5.txt

memory:
	$(VALG) ./dijkstra map6.txt query6.txt
	$(VALG) ./dijkstra map5x5.txt query5x5.txt

clean:
	/bin/rm -f dijkstra
	/bin/rm -f *.o
