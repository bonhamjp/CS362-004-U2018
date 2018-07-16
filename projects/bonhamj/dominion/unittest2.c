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
  printf("  #1 returns the hand count for the current user\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // returns hand card for position specified, for current player
  testState->whoseTurn = 0;
  assert(handCard(0 , testState) == testState->hand[0][0]);
  assertionsPassed++;
  assert(handCard(1 , testState) == testState->hand[0][1]);
  assertionsPassed++;
  assert(handCard((testState->handCount[0] - 1) , testState) == testState->hand[0][(testState->handCount[0] - 1)]);
  assertionsPassed++;

  testState->whoseTurn = 1;
  assert(handCard(0 , testState) == testState->hand[1][0]);
  assertionsPassed++;
  assert(handCard(1 , testState) == testState->hand[1][1]);
  assertionsPassed++;
  assert(handCard((testState->handCount[1] - 1) , testState) == testState->hand[1][(testState->handCount[1] - 1)]);
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
