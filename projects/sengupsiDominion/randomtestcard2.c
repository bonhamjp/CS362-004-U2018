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

// keeps running tally of test results
struct testResults {
  int passedTests;
  int failedTests;
};

// prints test results
void print_test_results(struct testResults* results) {
  // give success/failure counts
  printf("%i tests run\n\n", results->passedTests + results->failedTests);
  printf("SUCCESS: %i\n", results->passedTests);
  printf("FAILURE: %i\n", results->failedTests);
  printf("------------------------\n\n");
}

// non-halting assert
void j_assert(_Bool assertionPassed, struct testResults* results) {
  // test passed
  if(assertionPassed) {
    results->passedTests++;

  // test failed
  } else {
    results->failedTests++;
  }
}

// randomize test state
void test_randomized_smithy(struct gameState* testState, struct testResults* results) {
  // fill entire structure with totally random bytes
  int i;
  for(i = 0;i < sizeof(struct gameState);i++) {
    // randomize each byte
    ((char*) testState)[i] = floor(rand() * 256);
  }

  // select a random number of players, between 2, and MAX_PLAYERS
  int maxPlayers = rand() % MAX_PLAYERS;
  if(maxPlayers == 0 || maxPlayers == 1) {
    maxPlayers = 2;
  }
  testState->numPlayers = maxPlayers;

  // choose a random player
  int player = rand() % (maxPlayers - 1);
  testState->whoseTurn = player;

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
  int preWhoseTurn = testState->whoseTurn;
  int prePhase = testState->phase;
  int preNumActions = testState->numActions;
  int prePlayedCardCount = testState->playedCardCount;
  int preCoinCount = testState->coins;
  int preNumBuys = testState->numBuys;
  int preCopperCount = testState->supplyCount[copper];
  int preSilverCount = testState->supplyCount[silver];
  int preGoldCount = testState->supplyCount[gold];

  // play card with randomized state
  int result = cardEffect(smithy, choice1, choice2, choice3, testState, handPos, &bonus);

  // ** ORACLE ** //

  // post-state values
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];
  int postWhoseTurn = testState->whoseTurn;
  int postPhase = testState->phase;
  int postNumActions = testState->numActions;
  int postPlayedCardCount = testState->playedCardCount;
  int postCoinCount = testState->coins;
  int postNumBuys = testState->numBuys;
  int postCopperCount = testState->supplyCount[copper];
  int postSilverCount = testState->supplyCount[silver];
  int postGoldCount = testState->supplyCount[gold];

  // result is 0
  j_assert(result == 0, results);

  // 3 less cards in deck, after 3 drawn
  j_assert((preDeckCount - 3) == postDeckCount, results);

  // discard pile for player does not change
  j_assert(preDiscardCount == postDiscardCount, results);

  // hand grows by 2 cards. 3 were added, and 1 was discarded
  j_assert((preHandCount + 2) == postHandCount, results);

  // whose turn not altered
  j_assert(preWhoseTurn == postWhoseTurn, results);

  // phase is not altered
  j_assert(prePhase == postPhase, results);

  // numActions is not altered
  j_assert(preNumActions == postNumActions, results);

  // played cards count increases by 1
  j_assert((prePlayedCardCount + 1) == postPlayedCardCount, results);

  // coin count not altered
  j_assert(preCoinCount == postCoinCount, results);

  // numBuys count is not altered
  j_assert(preNumBuys == postNumBuys, results);

  // treasure supplies are not depleted
  j_assert(preCopperCount == postCopperCount, results);
  j_assert(preSilverCount == postSilverCount, results);
  j_assert(preGoldCount == postGoldCount, results);
}

// random test generator
void random_tests() {
  // gamestate for testing
  struct gameState testState;

  // track test results
  struct testResults results = { 0, 0 };

  // number of times random test run
  int i = 0;
  for(i = 0;i < RANDOM_RUNS;i++) {

    // randomize and test
    test_randomized_smithy(&testState, &results);
  }

  // print test results
  print_test_results(&results);
}

int main() {
  // use time for randomized seed
  srand (time(NULL));

  // output test title
  printf("Testing: %s \n------------------------\n\n", TEST_TITLE);

  // run random tests
  random_tests();
}
