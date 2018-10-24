CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = huffmain.o huff.o
VALG = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

# "make"" will create an executable called pa14
all: $(OBJS)
	$(GCC) $(OBJS) -o huff

huffmain.o: huffmain.c huff.c huff.h
	$(GCC) -c huffmain.c

huff.o: huffmain.c huff.c huff.h
	$(GCC) -c huff.c

# unhuff command
all2: unhuffmain.o unhuff.o
	$(GCC) unhuffmain.o unhuff.o -o unhuff

unhuffmain.o: unhuffmain.c unhuff.c unhuff.h
	$(GCC) -c unhuffmain.c

unhuff.o: unhuffmain.c unhuff.c unhuff.h
	$(GCC) -c unhuff.c

test2: all2
	./unhuff inputs/text0.txt.huff
	./unhuff inputs/text1.txt.huff
	./unhuff inputs/text2.txt.huff
	./unhuff inputs/text3.txt.huff
	./unhuff inputs/text4.txt.huff
	./unhuff inputs/text5.txt.huff

memory2: all2 test2
	$(VALG) ./unhuff inputs/text0.txt.huff
	$(VALG) ./unhuff inputs/text1.txt.huff
	$(VALG) ./unhuff inputs/text2.txt.huff
	$(VALG) ./unhuff inputs/text3.txt.huff
	$(VALG) ./unhuff inputs/text4.txt.huff
	$(VALG) ./unhuff inputs/text5.txt.huff

compare:
	diff inputs/text0.txt inputs/text0.txt.huff.unhuff
	diff inputs/text1.txt inputs/text1.txt.huff.unhuff
	diff inputs/text2.txt inputs/text2.txt.huff.unhuff
	diff inputs/text3.txt inputs/text3.txt.huff.unhuff
	diff inputs/text4.txt inputs/text4.txt.huff.unhuff
	diff inputs/text5.txt inputs/text5.txt.huff.unhuff

# "make test" will run huff
test: all
	./huff inputs/text0.txt
	./huff inputs/text1.txt
	./huff inputs/text2.txt
	./huff inputs/text3.txt
	./huff inputs/text4.txt
	./huff inputs/text5.txt

# "make memory" calls valgrind to check memory errors
memory: all test
	$(VALG) ./huff inputs/text0.txt
	$(VALG) ./huff inputs/text1.txt
	$(VALG) ./huff inputs/text2.txt
	$(VALG) ./huff inputs/text3.txt
	$(VALG) ./huff inputs/text4.txt
	$(VALG) ./huff inputs/text5.txt

# "make clean" remove .o and all output files
clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f huff unhuff
	/bin/rm -f inputs/*.huff
	/bin/rm -f inputs/*.unhuff
