// /***********************************
//  * Sidharth Sengupta
//  * Random Test 2 for Assignment 4
//  * Tests the great hall card
//  ************************************/
// #include "dominion.h"
// #include "dominion_helpers.h"
// #include "rngs.h"
// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>
// #include <time.h>
// #define NUMTRIES 100
//
// int asserttrue(int a, int b, char *error) {
//
//     if(a != b) {
//         printf("%s\n", error);
//         return 0;
//     }
//     return 1;
// }
//
// int main() {
//
//     int seed = 1000;
//     int numPlayer = 2;
//     int k[10] = {adventurer, council_room, feast, gardens, mine,
//                  remodel, smithy, village, baron, great_hall};
//     struct gameState G;
//     int x, i, j;
//     int p, size, top;
// 	srand(time(0));
//
//
//     printf("Random Card Test 3: Testing Great Hall\n");
//
// 	for(i = 0; i < NUMTRIES; i++) {
//
//         printf("Iteration %d\n", i + 1);
// 		initializeGame(numPlayer, k, seed, &G);
// 		p = rand() % 2;
// 		G.whoseTurn = p;
//
// 		if(p != 0) {
// 			for (j = 0; j < 5; j++)
// 				drawCard(G.whoseTurn, &G);
// 		}
// 		x = 1;
//
//         G.deckCount[p] = size = (rand() % 9) + 2;
//
//         for(j = 0; j < size; j++)
// 			G.deck[p][j] = k[rand() % 10];
//
// 		top = G.deck[p][size - 1];
//
// 		G.hand[p][0] = great_hall;
// 		playCard(0, 0, 0, 0, &G);
//
//         if(asserttrue(5, G.handCount[p], "Hand Count Failed") == 0 && x != 0)
//             x = 0;
//         if(asserttrue(top, G.hand[p][0], "Top Card Failed") == 0 && x != 0)
//             x = 0;
//         if(asserttrue(1, G.numActions, "Num Actions Failed") == 0 && x != 0)
//             x = 0;
//
// 		if(x)
//             printf("Random Card Test 3 Iteration %d Successfully Completed\n\n", i + 1);
//         else {
//             printf("Random Card Test 3 Iteration %d Failed\n", i + 1);
//             printf("Expected hand count: 5, actual: %d\n", G.handCount[p]);
//             printf("Expected top card: %d, actual: %d\n", top, G.hand[p][0]);
//             printf("Expected num actions: 1, actual: %d\n\n", G.numActions);
// 		}
//     }
//     return 0;
// }

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

// maximum number of cards in storage, or embargo
#define MAX_CARD_STOCK 5 // used to produce range (-1..4]
// maximum coins a player can have before player embargo
#define MAX_COINS 20 // used to produce range (0..19)

// keeps running tally of test results
struct testResults {
  int passedTests;
  int failedTests;
};

// prints test results
void print_test_results(struct testResults* results) {
  // give success/failure counts
  printf("%i tests run\n\n", results->passedTests + results->failedTests);
  printf("SUCCESS: %i\n", results->passedTests);
  printf("FAILURE: %i\n", results->failedTests);
  printf("------------------------\n\n");
}

// non-halting assert
void j_assert(_Bool assertionPassed, struct testResults* results) {
  // test passed
  if(assertionPassed) {
    results->passedTests++;

  // test failed
  } else {
    results->failedTests++;
  }
}

// randomize test state
void test_randomized_embargo(struct gameState* testState, struct testResults* results) {
  // fill entire structure with totally random bytes
  int i;
  for(i = 0;i < sizeof(struct gameState);i++) {
    // randomize each byte
    ((char*) testState)[i] = floor(rand() * 256);
  }

  // select a random number of players, between 2, and MAX_PLAYERS
  int maxPlayers = rand() % MAX_PLAYERS;
  if(maxPlayers == 0 || maxPlayers == 1) {
    maxPlayers = 2;
  }
  testState->numPlayers = maxPlayers;

  // choose a random player
  int player = rand() % (maxPlayers - 1);
  testState->whoseTurn = player;

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
  int preWhoseTurn = testState->whoseTurn;
  int prePhase = testState->phase;
  int preNumActions = testState->numActions;
  int prePlayedCardCount = testState->playedCardCount;
  int preNumBuys = testState->numBuys;
  int preCopperCount = testState->supplyCount[copper];
  int preSilverCount = testState->supplyCount[silver];
  int preGoldCount = testState->supplyCount[gold];

  // play card with randomized state
  int result = cardEffect(embargo, choice1, choice2, choice3, testState, handPos, &bonus);

  // ** ORACLE ** //

  // post-state values
  int postCoins = testState->coins;
  int postSupplyCount = testState->supplyCount[choice1];
  int postEmbargoCount = testState->embargoTokens[choice1];
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];
  int postWhoseTurn = testState->whoseTurn;
  int postPhase = testState->phase;
  int postNumActions = testState->numActions;
  int postPlayedCardCount = testState->playedCardCount;
  int postNumBuys = testState->numBuys;
  int postCopperCount = testState->supplyCount[copper];
  int postSilverCount = testState->supplyCount[silver];
  int postGoldCount = testState->supplyCount[gold];

  // always increments coins by 2
  j_assert((preCoins + 2) == postCoins, results);

  // if card player chose to embargo was not in supply
  if(preSupplyCount == -1) {
    // return value is -1
    j_assert(result == -1, results);

    // supply count for card does not change
    j_assert(preSupplyCount == postSupplyCount, results);

    // embargo token for card does not change
    j_assert(preEmbargoCount == postEmbargoCount, results);

    // no cards are removed from deck
    j_assert(preDeckCount == postDeckCount, results);

    // no cards are removed from hand
    j_assert(preHandCount == postHandCount, results);

    // no cards are removed from discard
    j_assert(preDiscardCount == postDiscardCount, results);

  // else card was still in stock
  } else {
    // return value is 0
    j_assert(result == 0, results);

    // supply count for card does not change
    j_assert(preSupplyCount == postSupplyCount, results);

    // embargo token for card does increases by 1
    j_assert((preEmbargoCount + 1) == postEmbargoCount, results);

    // no cards are removed from deck
    j_assert(preDeckCount == postDeckCount, results);

    // the players hand count goes down by 1, because current card is discarded
    j_assert((preHandCount - 1) == postHandCount, results);

    // no cards are removed from discard
    j_assert(preDiscardCount == postDiscardCount, results);
  }

  // whose turn not altered
  j_assert(preWhoseTurn == postWhoseTurn, results);

  // phase is not altered
  j_assert(prePhase == postPhase, results);

  // numActions is not altered
  j_assert(preNumActions == postNumActions, results);

  // played cards count not altered
  j_assert(prePlayedCardCount == postPlayedCardCount, results);

  // numBuys count is is not altered
  j_assert(preNumBuys == postNumBuys, results);

  // treasure supplies are not depleted
  j_assert(preCopperCount == postCopperCount, results);
  j_assert(preSilverCount == postSilverCount, results);
  j_assert(preGoldCount == postGoldCount, results);
}

// random test generator
void random_tests() {
  // gamestate for testing
  struct gameState testState;

  // track test results
  struct testResults results = { 0, 0 };

  // number of times random test run
  int i = 0;
  for(i = 0;i < RANDOM_RUNS;i++) {

    // randomize and test
    test_randomized_embargo(&testState, &results);
  }

  // print test results
  print_test_results(&results);
}

int main() {
  // use time for randomized seed
  srand (time(NULL));

  // output test title
  printf("Testing: %s \n------------------------\n\n", TEST_TITLE);

  // run random tests
  random_tests();
}
