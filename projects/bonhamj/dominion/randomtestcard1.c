/*
*  randomtestcard1.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  randomtestcard1: randomtestcard1.c dominion.o rngs.o
*  gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TEST_TITLE "Embargo Random Testing"

// number of random iterations to do
#define RANDOM_RUNS 9999

// TODO: lookup realisticmax card stock, embargo and coins during player turn
// maximum number of cards in storage, or embargo
#define MAX_CARD_STOCK 5 // used to produce range (-1..4]
// maximum coins a player can have before player embargo
#define MAX_COINS 20 // used to produce range (0..19)

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

// randomize test state
void test_randomized_embargo(struct gameState* testState) {
  // fill entire structure with totally random bytes
  int i;
  for(i = 0;i < sizeof(struct gameState);i++) {
    // randomize each byte
    ((char*) testState)[i] = floor(random() * 256);
  }

  // choose a random player
  int player = rand() % MAX_PLAYERS;
  testState->whoseTurn = player;

  // TODO: set random number of players
  testState->numPlayers = MAX_PLAYERS;

  // set randomized cards for player
  int playerDeckCount = rand() % (MAX_DECK - 1);
  testState->deckCount[player] = playerDeckCount;
  for(i = 0;i < playerDeckCount;i++) {
    testState->deck[player][i] = rand() % (treasure_map + 1);
  }

  int playerDiscountCount = rand() % (MAX_DECK - 1);
  testState->discardCount[player] = playerDiscountCount;
  for(i = 0;i < playerDiscountCount;i++) {
    testState->discard[player][i] = rand() % (treasure_map + 1);
  }

  int playerHandCount = rand() % (MAX_HAND - 1);
  testState->handCount[player] = playerHandCount;
  for(i = 0;i < playerHandCount;i++) {
    testState->hand[player][i] = rand() % (treasure_map + 1);
  }

  // randomize card counts in stock and embargo
  for(i = 0;i < (treasure_map + 1);i++) {
    // allows for possible out of stock supply card
    testState->supplyCount[i] = (rand() % MAX_CARD_STOCK) - 1;
    testState->embargoTokens[i] = rand() % MAX_CARD_STOCK;
  }

  // randomize the number of coins the player starts with
  testState->coins = rand() % MAX_COINS;

  // choice1 is set to random card, the others are not used
  int choice1 = rand() % (treasure_map + 1);
  int choice2 = 0;
  int choice3 = 0;

  // randomly choose a card position, from players hand
  int handPos = 0;
  if(playerHandCount > 0) {
    handPos = rand() % playerHandCount;
  }

  // bonus is not used
  int bonus = 0;

  // pre-state values
  int preCoins = testState->coins;
  int preSupplyCount = testState->supplyCount[choice1];
  int preEmbargoCount = testState->embargoTokens[choice1];
  int preDeckCount = testState->deckCount[player];
  int preDiscardCount = testState->discardCount[player];
  int preHandCount = testState->handCount[player];

  // play card with randomized state
  int result = cardEffect(embargo, choice1, choice2, choice3, testState, handPos, &bonus);

  // post-state values
  int postCoins = testState->coins;
  int postSupplyCount = testState->supplyCount[choice1];
  int postEmbargoCount = testState->embargoTokens[choice1];
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];

  // always increments coins by 2
  j_assert((preCoins + 2) == postCoins);

  // if card player chose to embargo was not in supply
  if(preSupplyCount == -1) {
    // printf("WAS OUT OF STOCK!\n");
    // return value is -1
    j_assert(result == -1);

    // supply count for card does not change
    j_assert(preSupplyCount == postSupplyCount);

    // embargo token for card does not change
    j_assert(preEmbargoCount == postEmbargoCount);

    // no cards are removed from deck
    j_assert(preDeckCount == postDeckCount);

    // no cards are removed from hand
    j_assert(preHandCount == postHandCount);

    // no cards are removed from discard
    j_assert(preDiscardCount == postDiscardCount);

  // else card was still in stock
  } else {
    // printf("WAS IN STOCK!\n");
    // return value is 0
    j_assert(result == 0);

    // supply count for card does not change
    j_assert(preSupplyCount == postSupplyCount);

    // embargo token for card does increases by 1
    j_assert((preEmbargoCount + 1) == postEmbargoCount);

    // no cards are removed from deck
    j_assert(preDeckCount == postDeckCount);

    // the players hand count goes down by 1, because current card is discarded
    j_assert((preHandCount - 1) == postHandCount);

    // no cards are removed from discard
    j_assert(preDiscardCount == postDiscardCount);
  }
}

// random test generator
void random_tests() {
  struct gameState testState;

  // number of times random test run
  int i = 0;
  for(i = 0;i < RANDOM_RUNS;i++) {

    // randomize and test
    test_randomized_embargo(&testState);
  }

  // go to next line
  printf("\n");
}

int main() {
  // use time for randomized seed
  srand (time(NULL));

  // output test title
  printf("Testing: %s \n------------------------\n\n", TEST_TITLE);

  // run random tests
  random_tests();
}
