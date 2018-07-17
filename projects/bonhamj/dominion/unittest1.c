/*
*  unittest1.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  unittest1: unittest1.c dominion.o rngs.o
*  gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNCTION "buyCard"

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

void setup_test(struct gameState* freshState, struct gameState* testState, int supplyPos) {
  // copy fresh state
  memcpy(testState, freshState, sizeof(struct gameState));
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 the current player does not have any buys left\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 0;

  // ASSERTIONS
  // returns -1 if the player has no buys
  j_assert(buyCard(minion, testState) == -1);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 player has buys left, but no cards are left in supply, for card specified\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[salvager] = 0;

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  j_assert(buyCard(minion, testState) == -1);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 player can buy, and there are enough cards in supply, but player does not have enough coins\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[baron] = 1;
  testState->coins = getCost(baron) - 1; // cannot afford baron

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  j_assert(buyCard(baron, testState) == -1);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 player can buy, and there are enough cards in supply, and the player does have enough coins\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  int returnValue = buyCard(remodel, testState);

  // ASSERTIONS
  // state phase changes
  j_assert(freshState->phase != testState->phase);

  // state phase goes to 1
  j_assert(testState->phase == 1);

  // wrong! should be added to hand!
  // card added to discard
  j_assert(testState->discardCount[0] == 1);

  // discard count increases
  j_assert(testState->discard[0][0] == remodel);

  // card count subtracted from coins
  j_assert((freshState->coins - getCost(remodel)) == testState->coins);

  // number of buys count subtracted by 1
  j_assert((freshState->numBuys - 1) == testState->numBuys);

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

  return 0;
}
