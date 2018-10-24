all:
	gcc -Werror -Wall -g sorting.c sorting_main.c -o proj1

test: all
	./proj1

memory: all test
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./proj1 1000.txt testout.txt testseq1.txt testseq2.txt

clean:
	/bin/rm -f proj1
	/bin/rm -f testout.txt
	/bin/rm -f testseq1.txt
	/bin/rm -f testseq2.txt
