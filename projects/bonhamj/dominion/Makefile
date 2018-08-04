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

unittestresults: cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o interface.o rngs.o
	touch unittestresults.out

	gcc -o cardtest1 -g cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest2 -g cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest3 -g cardtest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o cardtest4 -g cardtest4.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest1 -g unittest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest2 -g unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest3 -g unittest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unittest4 -g unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)

	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out

	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: randomtestadventurer.c randomtestcard1.c randomtestcard2.c dominion.c interface.c rngs.c
	touch randomtestadventurer.out
	touch randomtestcard1.out
	touch randomtestcard2.out

	gcc -o randomtestadventurer -g randomtestadventurer.c -g dominion.c rngs.c interface.c $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

	gcc -o randomtestcard1 -g randomtestcard1.c -g dominion.c rngs.c interface.c $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -f -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

	gcc -o randomtestcard2 -g randomtestcard2.c -g dominion.c rngs.c interface.c $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 unittestresults.out randomtestadventurer randomtestcard1 randomtestcard2 randomtestadventurer.out randomtestcard1.out randomtestcard2.out
