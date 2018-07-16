/*
*  cardtest1.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  cardtest4: cardtest4.c dominion.o rngs.o
*  gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "Smithy"

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

void setup_test(struct gameState* freshState, struct gameState* testState, int handPos) {
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(smithy, 0, 0, 0, testState, handPos, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #1 draws 2 cards from the players deck, if there are at least 2 cards in deck\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // 1 more cards in players hand then when started- current card discarded, then 2 added
  assert((freshState->handCount[0] + 1) == testState->handCount[0]);
  assertionsPassed++;

  // does not add cards to other play hands
  assert((freshState->handCount[1]) == testState->handCount[1]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #2 removes 2 cards from players deck, if there are at least 2 cards in deck\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // 2 less cards in players deck
  assert((freshState->deckCount[0] - 2) == testState->deckCount[0]);
  assertionsPassed++;

  // does not remove cards from other players decks
  assert((freshState->deckCount[1]) == testState->deckCount[1]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #3 removes re-shuffles player discardsd into deck, and draws 2 cards, if not enough in deck\n");

  // SETUP
  int assertionsPassed = 0;

  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // no cards in deck to draw, only discard
  testState->discard[0][0] = testState->deck[0][0];
  testState->discard[0][1] = testState->deck[0][1];
  testState->discard[0][2] = testState->deck[0][2];
  testState->discard[0][3] = testState->deck[0][3];
  testState->discard[0][4] = testState->deck[0][4];
  testState->discardCount[0] = 5;
  testState->deckCount[0] = 0;

  // printf("deck count: %i\n", testState->deckCount[  0]);
  // printf("discard count: %i\n", testState->discardCount[0]);

  cardEffect(smithy, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // removes all discarded cards for player, to add them to deck
  assert(testState->discardCount[0] == 0);
  assertionsPassed++;

  // does not change discard cards for other players
  assert((freshState->discardCount[1]) == testState->discardCount[1]);
  assertionsPassed++;

  // adds 3 cards to player deck
  assert(testState->deckCount[0] == 3);
  assertionsPassed++;

  // does not change other players deck counts
  assert(freshState->deckCount[1] == testState->deckCount[1]);
  assertionsPassed++;

  // adds 1 to player hand
  assert((freshState->handCount[0] + 1) == testState->handCount[0]);
  assertionsPassed++;

  // does not change other players hand counts
  assert(freshState->handCount[1] == testState->handCount[1]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #4 plays the current card\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // adds a card players played pile
  assert((freshState->playedCardCount + 1) == testState->playedCardCount);
  assertionsPassed++;

  // the handPos card changes
  assert(freshState->hand[0][0] != testState->hand[0][0]);
  assertionsPassed++;

  // other players card in hand position do not move
  assert(freshState->hand[1][0] == testState->hand[1][0]);
  assertionsPassed++;

  // PRINT TEST RESULTS
  print_test_results(assertionsPassed);
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 discard card count does not increase\n");

  // SETUP
  int assertionsPassed = 0;
  setup_test(freshState, testState, 0);

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
