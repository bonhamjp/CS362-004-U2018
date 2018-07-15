/*
*  cardtest1.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  cardtest1: cardtest1.c dominion.o rngs.o
*  gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "Adventurer"

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
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 draws an extra copper card into hand, from player deck\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // an extra treasure card was drawn from players deck
  assert((freshState->handCount[0] + 1) == testState->handCount[0]);
  assertionsPassed++;

  // calculate starting copper
  int startingCopperInHand = 0;
  for(int i = 0;i < freshState->handCount[0];i++) {
    if(freshState->hand[0][i] == copper) {
      startingCopperInHand++;
    }
  }
  // calculate copper after adventurer card played
  int endingCopperInHand = 0;
  for(int i = 0;i < testState->handCount[0];i++) {
    if(testState->hand[0][i] == copper) {
      endingCopperInHand++;
    }
  }

  // the player has an extra copper in their hand now
  assert((startingCopperInHand + 1) == endingCopperInHand);
  assertionsPassed++;

  // the player has one less card in their hand, after removing a copper
  assert((freshState->deckCount[0] - 1) == testState->deckCount[0]);
  assertionsPassed++;

  // other players have the same number of cards in their hand
  assert(freshState->handCount[1] == testState->handCount[1]);
  assertionsPassed++;

  // other players have the same number of cards in their deck
  assert(freshState->deckCount[1] == testState->deckCount[1]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
    // TITLE
    printf("  #2 the supply of copper is not depleted\n");

    // SETUP
    int assertionsPassed = 0;
    setup_test(freshState, testState);

    // ASSERTIONS
    // the copper supply count has not changed
    assert(freshState->supplyCount[copper] == testState->supplyCount[copper]);
    assertionsPassed++;

    // PRINT TEST RESULTS
    print_test_results(assertionsPassed);
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 coin count is not altered\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // there are no added coins in play, after playing adventurer
  // starts with 4 coins
  assert(testState->coins == 4);
  assertionsPassed++;

  // same number of coins after playing adventurer, as beginning state
  assert(freshState->coins == testState->coins);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 discard card count does not increase\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // the discard card count stays the same, for the player
  assert(freshState->discardCount[0] == testState->discardCount[0]);
  assertionsPassed++;

  // the discard card count stays the same, for other players
  assert(freshState->discardCount[1] == testState->discardCount[1]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 played card count does not increase\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState);

  // ASSERTIONS
  // the played card count stays the same
  assert(freshState->playedCardCount == testState->playedCardCount);
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
  printf("Testing: %s card \n------------------------\n\n", TESTCARD);

  // run each test
  test_scenario_1(&freshState, &testState);
  test_scenario_2(&freshState, &testState);
  test_scenario_3(&freshState, &testState);
  test_scenario_4(&freshState, &testState);
  test_scenario_5(&freshState, &testState);

  return 0;
}
