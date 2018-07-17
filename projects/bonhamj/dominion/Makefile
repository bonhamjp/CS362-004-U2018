CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	# output file for unittests
	touch unittestresults.out

	# run card test 1, with gcov
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c -coverage -fpic -lm
	./cardtest1
	echo "Card Test1: \n--------------------" >> unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run card test 2, with gcov
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c -coverage -fpic -lm
	./cardtest2
	echo "Card Test2: \n--------------------" >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run card test 3, with gcov
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c -coverage -fpic -lm
	./cardtest3
	echo "Card Test3: \n--------------------" >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run card test 4, with gcov
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c -coverage -fpic -lm
	./cardtest4
	echo "Card Test4: \n--------------------" >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run unit test 1, with gcov
	gcc -o unittest1 unittest1.c dominion.c rngs.c -coverage -fpic -lm
	./unittest1
	echo "Unit Test1: \n--------------------" >> unittestresults.out
	gcov unittest1.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run unit test 2, with gcov
	gcc -o unittest2 unittest2.c dominion.c rngs.c -coverage -fpic -lm
	./unittest2
	echo "Unit Test2: \n--------------------" >> unittestresults.out
	gcov unittest2.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run unit test 3, with gcov
	gcc -o unittest3 unittest3.c dominion.c rngs.c -coverage -fpic -lm
	./unittest3
	echo "Unit Test3: \n--------------------" >> unittestresults.out
	gcov unittest3.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

	# run unit test 4, with gcov
	gcc -o unittest4 unittest4.c dominion.c rngs.c -coverage -fpic -lm
	./unittest4
	echo "Unit Test4: \n--------------------" >> unittestresults.out
	gcov unittest4.c >> unittestresults.out
	gcov dominion.c >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 unittestresults.out
