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
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 draws two extra treasure cards into hand, from player deck\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // two extra treasure cards are drawn from players deck
  j_assert((freshState->handCount[0] + 2) == testState->handCount[0]);

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

  // the player has two extra copper in their hand now
  j_assert((startingCopperInHand + 2) == endingCopperInHand);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
    // TITLE
    printf("  #2 the supply of copper is not depleted\n    ");

    // SETUP
    setup_test(freshState, testState);

    // ASSERTIONS
    // the copper supply count has not changed
    j_assert(freshState->supplyCount[copper] == testState->supplyCount[copper]);

    // clear line for next test
    printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 coin count is not altered\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // there are no added coins in play, after playing adventurer
  // starts with 4 coins
  j_assert(testState->coins == 4);

  // same number of coins after playing adventurer, as beginning state
  j_assert(freshState->coins == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 hand increases by 2\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // the player has two more cards in their hand, after adding two copper
  j_assert((freshState->handCount[0] + 2) == testState->handCount[0]);

  // other players have the same number of cards in their hand
  j_assert(freshState->handCount[1] == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 the user deck decreases number of non-treasure cards, + treausre cards drawn\n    ");

  // SETUP
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // first cards are treasure cards
  // only remove 2 cards from deck
  testState->deckCount[0] = 5;
  testState->deck[0][3] = copper;
  testState->deck[0][4] = copper;

  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // the player has three less cards in deck, -2 treasure, -1 adventurer
  j_assert((freshState->deckCount[0] - 2) == testState->deckCount[0]);

  // SETUP
  // play card, from fresh state
  memcpy(testState, freshState, sizeof(struct gameState));

  // first card is not treasure
  // only remove 2 cards from deck for treaures, plus first non treausre cards
  testState->deckCount[0] = 5;
  testState->deck[0][2] = copper;
  testState->deck[0][3] = copper;
  testState->deck[0][4] = estate;

  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // the player has three less cards in deck, -2 treasure, -1 adventurer
  j_assert((freshState->deckCount[0] - 3) == testState->deckCount[0]);

  // other players have the same number of cards in their deck
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 discard card count increases by cards drawn from deck that are not treasure cards\n    ");

  // SETUP
  // play card, from fresh state
  memcpy(testState, freshState, sizeof(struct gameState));

  // first cards are treasure cards
  // so no cards are discarded
  testState->deckCount[0] = 5;
  testState->deck[0][3] = copper;
  testState->deck[0][4] = copper;

  int bonus;
  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // the player discard card count does not increase
  j_assert((freshState->discardCount[0]) == testState->discardCount[0]);

  // SETUP
  // play card, from fresh state
  memcpy(testState, freshState, sizeof(struct gameState));

  // first cards are not treasure cards
  // so cards are discarded
  testState->deckCount[0] = 5;
  testState->deck[0][2] = copper;
  testState->deck[0][3] = copper;
  testState->deck[0][4] = estate;

  cardEffect(adventurer, 0, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // the discard card count increases by the number of non-treasure cards, for player
  j_assert((freshState->discardCount[0] + 1) == testState->discardCount[0]);

  // the discard card count of other players does not change
  j_assert((freshState->discardCount[1]) == testState->discardCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 played card count does not increase\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // the played card count stays the same
  j_assert(freshState->playedCardCount == testState->playedCardCount);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // whoseTurn have not changed
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // outpostPlayed have not changed
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change phase\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // phase have not changed
  j_assert(freshState->phase == testState->phase);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numActions have not changed
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_12(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #12 does not change numBuys\n    ");

  // SETUP
  setup_test(freshState, testState);

  // ASSERTIONS
  // numBuys have not changed
  j_assert(freshState->numBuys == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_13(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #13 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState);

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
  test_scenario_12(&freshState, &testState);
  test_scenario_13(&freshState, &testState);

  return 0;
}
