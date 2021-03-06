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
  printf("  #1 the current player does not have any buys left, returns -1\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 0;

  // ASSERTIONS
  // returns -1 if the player has no buys
  j_assert(buyCard(minion, testState) == -1);

  // hand count stays the same for player
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // hand count stays the same for other players
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 player has buys left, but no cards are left in supply, for card specified returns -1\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[minion] = 0;

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  j_assert(buyCard(minion, testState) == -1);

  // hand count stays the same for player
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // hand count stays the same for other players
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 player can buy, and there are enough cards in supply, but player does not have enough coins, returns -1\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[baron] = 1;
  testState->coins = getCost(baron) - 1; // cannot afford baron

  // ASSERTIONS
  // returns -1 if the there are no cards left in supply
  j_assert(buyCard(baron, testState) == -1);

  // hand count stays the same for player
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // hand count stays the same for other players
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 player can buy, and there are enough cards in supply, and the player does have enough coins, adds to discard\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  buyCard(remodel, testState);

  // ASSERTIONS
  // state phase changes
  j_assert(freshState->phase != testState->phase);

  // state phase goes to 1
  j_assert(testState->phase == 1);

  // card added to discard of player
  j_assert((freshState->discardCount[0] + 1) == testState->discardCount[0]);

  // discard stays the same for other players
  j_assert((freshState->discardCount[1]) == testState->discardCount[1]);

  // card count subtracted from coins
  j_assert((freshState->coins - getCost(remodel)) == testState->coins);

  // number of buys count subtracted by 1
  j_assert((freshState->numBuys - 1) == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 player can buy, and there are enough cards in supply, and the player does have enough coins, hand does not change\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  buyCard(remodel, testState);

  // ASSERTIONS
  // hand count stays the same for player
  j_assert(freshState->handCount[0] == testState->handCount[0]);

  // hand count  stays the same for other players
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 does not change deckCounts \n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // current player deckCount not changed
  buyCard(remodel, testState);
  j_assert(freshState->deckCount[0] == testState->deckCount[0]);

  // other player deckCount not changed
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // whoseTurn have not changed
  buyCard(remodel, testState);
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // outpostPlayed have not changed
  buyCard(remodel, testState);
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // numActions have not changed
  buyCard(remodel, testState);
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // numPlayers have not changed
  buyCard(remodel, testState);
  j_assert(freshState->numPlayers == testState->numPlayers);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change playedCardCount \n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  testState->numBuys = 1;
  testState->supplyCount[remodel] = 1;
  testState->coins = getCost(remodel); // can afford remodel

  // ASSERTIONS
  // playedCardCount have not changed
  buyCard(remodel, testState);
  j_assert(freshState->playedCardCount == testState->playedCardCount);

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

  return 0;
}
