/*
*  unittest4.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  unittest4: unittest4.c dominion.o rngs.o
*  gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTFUNCTION "updateCoins"

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
  printf("  #1 adds up treasure card amounts to coin total\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // adds 1 for each copper
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = copper;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 2);

  // adds 2 for each silver
  testState->handCount[0] = 2;
  testState->hand[0][0] = silver;
  testState->hand[0][1] = silver;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 4);

  // adds 3 for each gold
  testState->handCount[0] = 2;
  testState->hand[0][0] = gold;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 6);

  // adds up copper and silver together
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = silver;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 3);

  // adds up copper and gold together
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 4);

  // adds up silver and gold together
  testState->handCount[0] = 2;
  testState->hand[0][0] = silver;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 5);

  // adds up copper silver and gold together
  testState->handCount[0] = 3;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = silver;
  testState->hand[0][2] = gold;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 6);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 adds bonus amount to treasure total\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // adds bonus on top of copper
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = copper;
  updateCoins(0, testState, 1);
  j_assert(testState->coins == 3);

  // adds bonus on top of silver
  testState->handCount[0] = 2;
  testState->hand[0][0] = silver;
  testState->hand[0][1] = silver;
  updateCoins(0, testState, 2);
  j_assert(testState->coins == 6);

  // adds bonus on top of gold
  testState->handCount[0] = 2;
  testState->hand[0][0] = gold;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 3);
  j_assert(testState->coins == 9);

  // adds bonus on top of copper and silver together
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = silver;
  updateCoins(0, testState, 4);
  j_assert(testState->coins == 7);

  // adds bonus on top of copper and gold together
  testState->handCount[0] = 2;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 5);
  j_assert(testState->coins == 9);

  // adds bonus on top of silver and gold together
  testState->handCount[0] = 2;
  testState->hand[0][0] = silver;
  testState->hand[0][1] = gold;
  updateCoins(0, testState, 6);
  j_assert(testState->coins == 11);

  // adds bonus on top of copper silver and gold together
  testState->handCount[0] = 3;
  testState->hand[0][0] = copper;
  testState->hand[0][1] = silver;
  testState->hand[0][2] = gold;
  updateCoins(0, testState, 7);
  j_assert(testState->coins == 13);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 returns 0 if no treasure cards in hand\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // 0 treasure cards in hand, without bonus
  testState->handCount[0] = 2;
  testState->hand[0][0] = adventurer;
  testState->hand[0][1] = sea_hag;
  updateCoins(0, testState, 0);
  j_assert(testState->coins == 0);

  // 0 treasure cards in hand, with bonus
  testState->handCount[0] = 2;
  testState->hand[0][0] = steward;
  testState->hand[0][1] = embargo;
  updateCoins(0, testState, 42);
  j_assert(testState->coins == 42);

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

  return 0;
}
