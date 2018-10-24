VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

all:
	gcc -Werror -Wall -g adjacent.c -o adjacent

test: all
	./adjacent map6.txt
	./adjacent example.txt
	./adjacent map5x5.txt

memory:
	$(VALG) ./adjacent map6.txt
	$(VALG) ./adjacent example.txt
	$(VALG) ./adjacent map5x5.txt

clean:
	/bin/rm -f adjacent	
