/*
*  unittest2.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  unittest2: unittest2.c dominion.o rngs.o
*  gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNCTION "handCard"

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
  printf("  #1 returns the hand card at position for the current user\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // returns hand card for position specified, for current player
  testState->whoseTurn = 0;
  j_assert(handCard(0, testState) == testState->hand[0][0]);
  j_assert(handCard(1, testState) == testState->hand[0][1]);
  j_assert(handCard((testState->handCount[0] - 1) , testState) == testState->hand[0][(testState->handCount[0] - 1)]);

  testState->whoseTurn = 1;
  j_assert(handCard(0, testState) == testState->hand[1][0]);
  j_assert(handCard(1, testState) == testState->hand[1][1]);
  j_assert(handCard((testState->handCount[1] - 1) , testState) == testState->hand[1][(testState->handCount[1] - 1)]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 does not return incorrect card at position for the current user\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // does not return incorrect card
  testState->whoseTurn = 0;
  testState->handCount[0] = 5;
  testState->hand[0][0] = gold;
  testState->hand[0][1] = gold;
  testState->hand[0][2] = copper;
  testState->hand[0][3] = gold;
  testState->hand[0][4] = gold;

  j_assert(handCard(0, testState) != copper);
  j_assert(handCard(1, testState) != copper);
  j_assert(handCard(2, testState) != gold);
  j_assert(handCard(3, testState) != copper);
  j_assert(handCard(4, testState) != copper);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 does not change coins\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // coins have not changed
  handCard(0, testState);
  j_assert(freshState->coins == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // whoseTurn have not changed
  handCard(0, testState);
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // outpostPlayed have not changed
  handCard(0, testState);
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 does not change phase\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // phase have not changed
  handCard(0, testState);
  j_assert(freshState->phase == testState->phase);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numActions have not changed
  handCard(0, testState);
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 does not change numBuys\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numBuys have not changed
  handCard(0, testState);
  j_assert(freshState->numBuys == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numPlayers have not changed
  handCard(0, testState);
  j_assert(freshState->numPlayers == testState->numPlayers);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change playedCardCount \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // playedCardCount have not changed
  handCard(0, testState);
  j_assert(freshState->playedCardCount == testState->playedCardCount);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change handCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player handCount not changed
  handCard(0, testState);
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // other player handCount not changed
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_12(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #12 does not change deckCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player deckCount not changed
  handCard(0, testState);
  j_assert(freshState->deckCount[0] == testState->deckCount[0]);

  // other player deckCount not changed
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_13(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #13 does not change discardCounts \n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // current player discardCount not changed
  handCard(0, testState);
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
  int bonus = 0;

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
