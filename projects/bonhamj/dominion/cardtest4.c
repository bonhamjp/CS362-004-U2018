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

void setup_test(struct gameState* freshState, struct gameState* testState, int handPos) {
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(smithy, 0, 0, 0, testState, handPos, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  // TODO: supposed to draw 3 cards
  printf("  #1 draws 3 cards from the players deck, if there are at least 3 cards in deck\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // 1 more cards in players hand then when started- current card discarded, then 3 added
  j_assert((freshState->handCount[0] + 2) == testState->handCount[0]);

  // does not add cards to other play hands
  j_assert((freshState->handCount[1]) == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 removes 3 cards from players deck, if there are at least 3 cards in deck\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // 2 less cards in players deck
  j_assert((freshState->deckCount[0] - 3) == testState->deckCount[0]);

  // does not remove cards from other players decks
  j_assert((freshState->deckCount[1]) == testState->deckCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 re-shuffles player discards into deck, and draws 3 cards, if not enough in deck\n    ");

  // SETUP
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

  cardEffect(smithy, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // removes all discarded cards for player, to add them to deck
  j_assert(testState->discardCount[0] == 0);

  // does not change discard cards for other players
  j_assert((freshState->discardCount[1]) == testState->discardCount[1]);

  // adds 2 cards to player deck
  j_assert(testState->deckCount[0] == 2);

  // does not change other players deck counts
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

  // adds 1 to player hand
  j_assert((freshState->handCount[0] + 2) == testState->handCount[0]);

  // does not change other players hand counts
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 plays the current card\n    ");

  // SETUP
  // setup_test(freshState, testState, 0);
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // test smithy in hand is replaced by first drawn card
  testState->handCount[0] = 5;
  testState->deckCount[0] = 5;
  testState->hand[0][4] = smithy;
  testState->deck[0][4] = copper;
  testState->deck[0][3] = copper;
  testState->deck[0][2] = copper;

  cardEffect(smithy, 0, 0, 0, testState, 4, &bonus);

  // ASSERTIONS
  // adds a card players played pile
  j_assert((freshState->playedCardCount + 1) == testState->playedCardCount);

  // the handPos card changes
  j_assert(testState->hand[0][4] == copper);

  // other players card in hand position do not move
  j_assert(freshState->hand[1][0] == testState->hand[1][0]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 discard card count does not increase\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // the discard card count stays the same, for the player
  j_assert(freshState->discardCount[0] == testState->discardCount[0]);

  // the discard card count stays the same, for other players
  j_assert(freshState->discardCount[1] == testState->discardCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // whoseTurn have not changed
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // outpostPlayed have not changed
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 does not change phase\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // phase have not changed
  j_assert(freshState->phase == testState->phase);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // numActions have not changed
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change numBuys\n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // numBuys have not changed
  j_assert(freshState->numBuys == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState, 0);

  // ASSERTIONS
  // numPlayers have not changed
  j_assert(freshState->numPlayers == testState->numPlayers);

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
  test_scenario_6(&freshState, &testState);
  test_scenario_7(&freshState, &testState);
  test_scenario_8(&freshState, &testState);
  test_scenario_9(&freshState, &testState);
  test_scenario_10(&freshState, &testState);
  test_scenario_11(&freshState, &testState);

  return 0;
}
