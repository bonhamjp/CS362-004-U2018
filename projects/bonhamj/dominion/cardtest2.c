/*
*  cardtest2.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  cardtest2: cardtest2.c dominion.o rngs.o
*  gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TESTCARD "Embargo"

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

void setup_test(struct gameState* freshState, struct gameState* testState, int choice1, int handPos) {
  // play card, from fresh state
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));
  cardEffect(embargo, choice1, 0, 0, testState, handPos, &bonus);
}

void test_scenario_1(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #1 adds 2 coins to players coins in play\n    ");

  // SETUP
  setup_test(freshState, testState, 0, 0);

  // ASSERTIONS
  // 3 more coins than when game started
  j_assert((freshState->coins + 2) == testState->coins);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_2(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #2 does not increase embargo count for coin, if supply choice is out\n    ");

  // SETUP
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // empty supply for choice1
  testState->supplyCount[copper] = -1;

  cardEffect(embargo, copper, 0, 0, testState, 0, &bonus);

  // ASSERTIONS
  // the embargo count for the chosen coin is not increased
  j_assert((freshState->embargoTokens[copper]) == testState->embargoTokens[copper]);

  // the embargo count for other coins are not increased
  j_assert((freshState->embargoTokens[silver]) == testState->embargoTokens[silver]);

  // the embargo count for other coins are not increased
  j_assert((freshState->embargoTokens[gold]) == testState->embargoTokens[gold]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_3(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #3 increases embargo count of coin, if supply choice is not out\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // the embargo count for the chosen coin is increased
  j_assert((freshState->embargoTokens[copper] + 1) == testState->embargoTokens[copper]);

  // the embargo count for other coins are not increased
  j_assert((freshState->embargoTokens[silver]) == testState->embargoTokens[silver]);

  // the embargo count for other coins are not increased
  j_assert((freshState->embargoTokens[gold]) == testState->embargoTokens[gold]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_4(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #4 hand count is decreased by 1, if supply choice is not out\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // the hand count decreases by 1
  j_assert((freshState->handCount[0] - 1) == testState->handCount[0]);

  // the hand count does not decrease for other players
  j_assert((freshState->handCount[1]) == testState->handCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_5(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #5 current card in hand is replaced by last card in hand, if supply choice is not out, and there are multiple cards in hand\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // the card from the last position in the hand is now in the place where the current card was
  j_assert((freshState->hand[0][freshState->handCount[0] - 1]) == testState->hand[0][0]);

  // the card from the first position does not change for other players
  j_assert((freshState->hand[1][0]) == testState->hand[1][0]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_6(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #6 current card in hand does not change, if supply choice is not out, and player discards last card\n    ");

  // SETUP
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // only two cards in hand
  testState->handCount[0] = 2;
  testState->hand[0][0] = freshState->hand[0][0];
  testState->hand[0][1] = freshState->hand[0][1];

  cardEffect(embargo, copper, 0, 0, testState, 1, &bonus);

  // ASSERTIONS
  // the card from first position is not changed for the player
  j_assert((freshState->hand[0][0]) == testState->hand[0][0]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_7(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #7 player is left with empty hand, if supply choice is not out, and there is only a single card in hand\n    ");

  // SETUP
  int bonus;
  memcpy(testState, freshState, sizeof(struct gameState));

  // only two cards in hand
  testState->handCount[0] = 1;
  testState->hand[0][0] = freshState->hand[0][0];

  cardEffect(embargo, copper, 0, 0, testState, 1, &bonus);

  // ASSERTIONS
  // the player has no cards in their hand
  j_assert(testState->handCount[0] == 0);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_8(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #8 discard card count does not increase\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // the discard card count stays the same, for the player
  j_assert(freshState->discardCount[0] == testState->discardCount[0]);

  // the discard card count stays the same, for other players
  j_assert(freshState->discardCount[1] == testState->discardCount[1]);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_9(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #9 played card count does not increase\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // the played card count stays the same
  j_assert(freshState->playedCardCount == testState->playedCardCount);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_10(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #10 does not change whoseTurn\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // whoseTurn have not changed
  j_assert(freshState->whoseTurn == testState->whoseTurn);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_11(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #11 does not change outpostPlayed\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // outpostPlayed have not changed
  j_assert(freshState->outpostPlayed == testState->outpostPlayed);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_12(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #12 does not change phase\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // phase have not changed
  j_assert(freshState->phase == testState->phase);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_13(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #13 does not change numActions\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // numActions have not changed
  j_assert(freshState->numActions == testState->numActions);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_14(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #14 does not change numBuys\n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // numBuys have not changed
  j_assert(freshState->numBuys == testState->numBuys);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_15(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #15 does not change numPlayers \n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // numPlayers have not changed
  j_assert(freshState->numPlayers == testState->numPlayers);

  // clear line for next test
  printf("\n\n");
}

void test_scenario_16(struct gameState* freshState, struct gameState* testState) {
  // TITLE
  printf("  #16 does not change deckCounts \n    ");

  // SETUP
  setup_test(freshState, testState, copper, 0);

  // ASSERTIONS
  // current player deckCount not changed
  j_assert(freshState->deckCount[0] == testState->deckCount[0]);

  // other player deckCount not changed
  j_assert(freshState->deckCount[1] == testState->deckCount[1]);

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
  test_scenario_14(&freshState, &testState);
  test_scenario_15(&freshState, &testState);
  test_scenario_16(&freshState, &testState);

  return 0;
}
