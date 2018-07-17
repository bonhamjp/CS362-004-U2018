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
  printf("  #1 returns the supply count, for the card specified\n    ");

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

  return 0;
}
