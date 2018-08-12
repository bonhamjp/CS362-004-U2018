/*
*  Include the following lines in your makefile:
*
*  randomadventurer: randomadventurer.c dominion.o rngs.o
*  gcc -o randomadventurer -g  randomadventurer.c dominion.o rngs.o $(CFLAGS)
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

// title of test
#define TEST_TITLE "Adventurer Random Testing"

// number of random iterations to do
#define RANDOM_RUNS 9999

// number of treasure needed to prevent adventurer infinite loop
#define MINIMUM_COPPER 3

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
void test_randomized_adventurer(struct gameState* testState, struct testResults* results) {
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
  // leave room for the minimum number of treasure cards
  int playerDeckCount = rand() % (MAX_DECK - 1);
  testState->deckCount[player] = playerDeckCount;
  for(i = 0;i < playerDeckCount;i++) {
    testState->deck[player][i] = rand() % (treasure_map + 1);
  }

  int playerDiscardCount = rand() % (MAX_DECK - 1);
  testState->discardCount[player] = playerDiscardCount;
  for(i = 0;i < playerDiscardCount;i++) {
    testState->discard[player][i] = rand() % (treasure_map + 1);
  }

  int playerHandCount = rand() % (MAX_HAND - 1);
  testState->handCount[player] = playerHandCount;
  for(i = 0;i < playerHandCount;i++) {
    testState->hand[player][i] = rand() % (treasure_map + 1);
  }

  // add three copper, since deck construction requires that,
  // and it prevents infinite loop if not enough treasure was randomly added
  // do in discard, so deck has a chance of being empty, to achieve full
  // code coverage
  int addedCopper = 0;
  while(addedCopper < MINIMUM_COPPER) {
    // add to deck, if it can fit more empty
    if(playerDiscardCount < (MAX_DECK - 1)) {
      // add random card to end of deck
      testState->deck[player][playerDiscardCount] = (treasure_map + 1);

      // increase deck count
      playerDiscardCount++;
      testState->discardCount[player] = playerDiscardCount;
    }

    // add copper card to random spot in deck
    int randomIndex = rand() % playerDiscardCount;
    if(testState->discard[player][randomIndex] != copper) {
      // add copper to random place in deck
      testState->discard[player][randomIndex] = copper;

      // increment copper added count
      addedCopper++;
    }
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
  int preTreasureCount = 0;
  for(i = 0;i < preHandCount;i++) {
    int card = testState->hand[player][i];
    if(card == copper || card == silver || card == gold) {
      preTreasureCount++;
    }
  }
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
  int result = cardEffect(adventurer, choice1, choice2, choice3, testState, handPos, &bonus);

  // ** ORACLE ** //

  // post-state values
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];
  int postTreasureCount = 0;
  for(i = 0;i < postHandCount;i++) {
    int card = testState->hand[player][i];
    if(card == copper || card == silver || card == gold) {
      postTreasureCount++;
    }
  }
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

  // deck and discard together lost 2 cards, which go to hand
  j_assert((preDeckCount + preDiscardCount - 2) == (postDeckCount + postDiscardCount), results);

  // hand grows by 2 cards
  j_assert((preHandCount + 2) == postHandCount, results);

  // treasure in hand increases by 2
  j_assert((preTreasureCount + 2) == postTreasureCount, results);

  // whose turn not altered
  j_assert(preWhoseTurn == postWhoseTurn, results);

  // phase is not altered
  j_assert(prePhase == postPhase, results);

  // numActions is not altered
  j_assert(preNumActions == postNumActions, results);

  // played cards count not altered
  j_assert(prePlayedCardCount == postPlayedCardCount, results);

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
    test_randomized_adventurer(&testState, &results);
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
