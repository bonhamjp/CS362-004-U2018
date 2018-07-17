/*
*  cardtest3.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  cardtest3: cardtest3.c dominion.o rngs.o
*  gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "Steward"

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

void setup_test(struct gameState* freshState, struct gameState* testState, int choice1, int choice2, int choice3, int handPos) {
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(steward, choice1, choice2, choice3, testState, handPos, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 choice 1 draws 2 cards for the player\n    ");

  // SETUP
  setup_test(freshState, testState, 1, 0, 0, 0);

  // ASSERTIONS
  // adds 2 cards to the players hand, while discarding the current card
  j_assert((freshState->handCount[0] + 1) == testState->handCount[0]);

  // does not add cards to other players hands
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // does not change coin count
  j_assert(freshState->coins == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 choice 2 adds 2 coins\n    ");

  // SETUP
  setup_test(freshState, testState, 2, 0, 0, 0);

  // ASSERTIONS
  // adds 2 coins
  j_assert((freshState->coins + 2) == testState->coins);

  // does not add cards to players hands, but removes current card
  j_assert((freshState->handCount[0] - 1) == testState->handCount[0]);

  // does not add cards to other players hands
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 choice 3 discards 2 cards from players hand, of players choice\n    ");

  // SETUP
  setup_test(freshState, testState, 3, 0, 1, 0);

  // ASSERTIONS
  // removes 2 cards player chose, plus card played
  j_assert((freshState->handCount[0] - 3) == testState->handCount[0]);

  // does not change other players card counts
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // replaces removed cards from last cards in players hand
  j_assert(freshState->hand[0][4] == testState->hand[0][0]);
  j_assert(freshState->hand[0][3] == testState->hand[0][1]);

  // does not replace cards from other players hands
  j_assert(freshState->hand[1][0] == testState->hand[1][0]);
  j_assert(freshState->hand[1][1] == testState->hand[1][1]);

  // does not change coin count
  j_assert(freshState->coins == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #4 plays the current card\n    ");

  // SETUP
  setup_test(freshState, testState, 1, 0, 0, 0);

  // ASSERTIONS
  // adds a card players played pile
  j_assert((freshState->playedCardCount + 1) == testState->playedCardCount);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 discard card count does not increase\n    ");

  // SETUP
  setup_test(freshState, testState, 1, 0, 0, 0);

  // ASSERTIONS
  // the discard card count stays the same, for the player
  j_assert(freshState->discardCount[0] == testState->discardCount[0]);

  // the discard card count stays the same, for other players
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
  printf("Testing: %s card \n------------------------\n\n", TESTCARD);

  // run each test
  test_scenario_1(&freshState, &testState);
  test_scenario_2(&freshState, &testState);
  test_scenario_3(&freshState, &testState);
  test_scenario_4(&freshState, &testState);
  test_scenario_5(&freshState, &testState);

  return 0;
}
