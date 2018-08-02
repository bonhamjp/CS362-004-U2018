/*
*  randomtestcard2.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  randomtestcard2: randomtestcard2.c dominion.o rngs.o
*  gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST_TITLE "Smithy Random Testing"

// number of random iterations to do
#define RANDOM_RUNS 9999

// non-halting assert
void j_assert(_Bool assertionPassed) {
  // test passed
  if(assertionPassed) {
    printf("+");

  // test failed
  } else {
    printf("f");
  }
}

// randomize test state
void test_randomized_smithy(struct gameState* testState) {
  // fill entire structure with totally random bytes
  int i;
  for(i = 0;i < sizeof(struct gameState);i++) {
    // randomize each byte
    ((char*) testState)[i] = floor(random() * 256);
  }

  // choose a random player
  int player = rand() % MAX_PLAYERS;
  testState->whoseTurn = player;

  // TODO: set random number of players
  testState->numPlayers = MAX_PLAYERS;

  // set randomized cards for player
  // make sure enough cards in deck and discard to draw at least 3
  int playerDeckCount = 3 + (rand() % (MAX_DECK - 3));
  testState->deckCount[player] = playerDeckCount;
  for(i = 0;i < playerDeckCount;i++) {
    testState->deck[player][i] = rand() % (treasure_map + 1);
  }

  int playerDiscountCount = 3 + (rand() % (MAX_DECK - 3));
  testState->discardCount[player] = playerDiscountCount;
  for(i = 0;i < playerDiscountCount;i++) {
    testState->discard[player][i] = rand() % (treasure_map + 1);
  }

  int playerHandCount = rand() % (MAX_HAND - 1);
  testState->handCount[player] = playerHandCount;
  for(i = 0;i < playerHandCount;i++) {
    testState->hand[player][i] = rand() % (treasure_map + 1);
  }

  // choices are never set
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;

  // randomly choose a card position, from players hand
  int handPos = 0;
  if(playerHandCount > 0) {
    handPos = rand() % playerHandCount;
  }

  // bonus is not used
  int bonus = 0;

  // pre-state values
  int preDeckCount = testState->deckCount[player];
  int preDiscardCount = testState->discardCount[player];
  int preHandCount = testState->handCount[player];

  // play card with randomized state
  cardEffect(smithy, choice1, choice2, choice3, testState, handPos, &bonus);

  // post-state values
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];

  // 3 less cards in deck, after 3 drawn
  j_assert((preDeckCount - 3) == postDeckCount);

  // discard pile for player does not change
  j_assert(preDiscardCount == postDiscardCount);

  // hand grows by 2 cards. 3 were added, and 1 was discarded
  j_assert((preHandCount + 2) == postHandCount);
}

// random test generator
void random_tests() {
  struct gameState testState;

  // number of times random test run
  int i = 0;
  for(i = 0;i < RANDOM_RUNS;i++) {

    // randomize and test
    test_randomized_smithy(&testState);
  }

  // go to next line
  printf("\n");
}

int main() {
  // use time for randomized seed
  srand (time(NULL));

  // output test title
  printf("Testing: %s \n------------------------\n\n", TEST_TITLE);

  // run random tests
  random_tests();
}
