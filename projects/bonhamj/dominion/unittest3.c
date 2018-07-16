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

void setup_test(struct gameState* freshState, struct gameState* testState) {
  // copy fresh state
  memcpy(testState, freshState, sizeof(struct gameState));
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 returns the supply count, for the card specified\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // card has no supply
  testState->supplyCount[sea_hag] = -1;
  assert(supplyCount(sea_hag , testState) == -1);
  assertionsPassed++;

  // card has some supply
  testState->supplyCount[great_hall] = 10;
  assert(supplyCount(great_hall, testState) == 10);
  assertionsPassed++;

  // card has many supply
  testState->supplyCount[gold] = MAX_DECK;
  assert(supplyCount(gold, testState) == MAX_DECK);
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

  return 0;
}
