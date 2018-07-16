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

void print_test_results(int assertionsPassed) {
  if(assertionsPassed > 0) {
    printf("    ");

    int i;
    for(i = 0;i < assertionsPassed;i++) {
      printf("+");
    }
    printf("\n\n");
  }
}

void setup_test(struct gameState* freshState, struct gameState* testState, int supplyPos) {
  // copy fresh state
  memcpy(testState, freshState, sizeof(struct gameState));
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 the current player does not have any buys left\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  testState->numBuys = 0;

  // ASSERTIONS
  // returns -1 if the player has no buys
  assert(buyCard(minion, testState) == -1);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 player has buys left, but no cards are left in supply, for card specified\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[salvager] = 0;

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  assert(buyCard(minion, testState) == -1);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 player can buy, and there are enough cards in supply, but player does not have enough coins\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[baron] = 1;
  testState->coins = getCost(baron) - 1; // cannot afford baron

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  assert(buyCard(baron, testState) == -1);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 player can buy, and there are enough cards in supply, and the player does have enough coins\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  int returnValue = buyCard(remodel, testState);

  // ASSERTIONS

  // state phase changes
  assert(freshState->phase != testState->phase);
  assertionsPassed++;

  // state phase goes to 1
  assert(testState->phase == 1);
  assertionsPassed++;

  // wrong! should be added to hand!
  // card added to discard
  assert(testState->discardCount[0] == 1);
  assertionsPassed++;

  // discard count increases
  assert(testState->discard[0][0] == remodel);
  assertionsPassed++;

  // card count subtracted from coins
  assert((freshState->coins - getCost(remodel)) == testState->coins);
  assertionsPassed++;

  // number of buys count subtracted by 1
  assert((freshState->numBuys - 1) == testState->numBuys);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
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
