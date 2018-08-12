/*
*  unittest3.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  unittest3: unittest3.c dominion.o rngs.o
*  gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNCTION "supplyCount"

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

void setup_test(struct gameState* freshState, struct gameState* testState) {
  // copy fresh state
  memcpy(testState, freshState, sizeof(struct gameState));
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 returns the supplyCount, for the card specified\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // card has no supply
  testState->supplyCount[sea_hag] = -1;
  j_assert(supplyCount(sea_hag , testState) == -1);

  // card has some supply
  testState->supplyCount[great_hall] = 10;
  j_assert(supplyCount(great_hall, testState) == 10);

  // card has many supply
  testState->supplyCount[gold] = MAX_DECK;
  j_assert(supplyCount(gold, testState) == MAX_DECK);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 does not change coins\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->coins == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // whoseTurn have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // outpostPlayed have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 does not change phase\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // phase have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->phase == testState->phase);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numActions have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 does not change numBuys\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numBuys have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->numBuys == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numPlayers have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->numPlayers == testState->numPlayers);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 does not change playedCardCount \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // playedCardCount have not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->playedCardCount == testState->playedCardCount);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change handCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player handCount not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // other player handCount not changed
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change deckCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player deckCount not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->deckCount[0] == testState->deckCount[0]);

  // other player deckCount not changed
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_12(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #12 does not change discardCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player discardCount not changed
  testState->supplyCount[sea_hag] = 1;
  supplyCount(sea_hag , testState);
  j_assert(freshState->discardCount[0] == testState->discardCount[0]);

  // other player discardCounts not changed
  j_assert(freshState->discardCount[1] == testState->discardCount[1]);

  // clear line for next test
  printf("\n\n");
}

int main() {
  // control test settings
  int numberOfPlayers = 2;
  int seed = 9999;

  // setup
  struct gameState freshState, testState;
  int cards[10] = {
    council_room,
    feast,
    gardens,
    mine,
    remodel,
    smithy,
    village,
    baron,
    great_hall,
    minion
  };

  // initialize game with test setup
  initializeGame(numberOfPlayers, cards, seed, &freshState);

  // run tests
  printf("Testing: %s function \n------------------------\n\n", TESTFUNCTION);

  // run each test
  test_scenario_1(&freshState, &testState);
  test_scenario_2(&freshState, &testState);
  test_scenario_3(&freshState, &testState);
  test_scenario_4(&freshState, &testState);
  test_scenario_5(&freshState, &testState);
  test_scenario_6(&freshState, &testState);
  test_scenario_7(&freshState, &testState);
  test_scenario_8(&freshState, &testState);
  test_scenario_9(&freshState, &testState);
  test_scenario_10(&freshState, &testState);
  test_scenario_11(&freshState, &testState);
  test_scenario_12(&freshState, &testState);

  return 0;
}
