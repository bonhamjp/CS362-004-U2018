/*
*  randomadventurer.c
*
*/

/*
*  Include the following lines in your makefile:
*
*  randomadventurer: randomadventurer.c dominion.o rngs.o
*  gcc -o randomadventurer -g  randomadventurer.c dominion.o rngs.o $(CFLAGS)
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

// title of test
#define TEST_TITLE "Adventurer Random Testing"

// number of random iterations to do
#define RANDOM_RUNS 9999

// number of treasure needed to prevent adventurer infinite loop
#define MINIMUM_COPPER 3

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
void test_randomized_adventurer(struct gameState* testState) {
  // fill entire structure with totally random bytes
  int i;
  for(i = 0;i < sizeof(struct gameState);i++) {
    // randomize each byte
    ((char*) testState)[i] = floor(random() * 256);
  }

  // choose a random player
  int player = rand() % (MAX_PLAYERS - 1);
  testState->whoseTurn = player;

  // TODO: set random number of players
  testState->numPlayers = MAX_PLAYERS;

  // set randomized cards for player
  // leave room for the minimum number of treasure cards
  int playerDeckCount = rand() % (MAX_DECK - 1);
  testState->deckCount[player] = playerDeckCount;
  for(i = 0;i < playerDeckCount;i++) {
    testState->deck[player][i] = rand() % (treasure_map + 1);
  }

  int playerDiscardCount = rand() % (MAX_DECK - 1);
  testState->discardCount[player] = playerDiscardCount;
  for(i = 0;i < playerDiscardCount;i++) {
    testState->discard[player][i] = rand() % (treasure_map + 1);
  }

  int playerHandCount = rand() % (MAX_HAND - 1);
  testState->handCount[player] = playerHandCount;
  for(i = 0;i < playerHandCount;i++) {
    testState->hand[player][i] = rand() % (treasure_map + 1);
  }

  // add three copper, since deck construction requires that,
  // and it prevents infinite loop if not enough treasure was randomly added
  // do in discard, so deck has a chance of being empty, to achieve full
  // code coverage
  int addedCopper = 0;
  while(addedCopper < MINIMUM_COPPER) {
    // add to deck, if it can fit more empty
    if(playerDiscardCount < (MAX_DECK - 1)) {
      // add random card to end of deck
      testState->deck[player][playerDiscardCount] = (treasure_map + 1);

      // increase deck count
      playerDiscardCount++;
      testState->discardCount[player] = playerDiscardCount;
    }

    // add copper card to random spot in deck
    int randomIndex = rand() % playerDiscardCount;
    if(testState->discard[player][randomIndex] != copper) {
      // add copper to random place in deck
      testState->discard[player][randomIndex] = copper;

      // increment copper added count
      addedCopper++;
    }
  }

  // choices are never set
  int choice1 = 0;
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
  int preDeckCount = testState->deckCount[player];
  int preDiscardCount = testState->discardCount[player];
  int preHandCount = testState->handCount[player];
  int preTreasureCount = 0;
  for(i = 0;i < preHandCount;i++) {
    int card = testState->hand[player][i];
    if(card == copper || card == silver || card == gold) {
      preTreasureCount++;
    }
  }

  // play card with randomized state
  cardEffect(adventurer, choice1, choice2, choice3, testState, handPos, &bonus);

  ////////////
  // ORACLE //
  ////////////

  // post-state values
  int postDeckCount = testState->deckCount[player];
  int postDiscardCount = testState->discardCount[player];
  int postHandCount = testState->handCount[player];
  int postTreasureCount = 0;
  for(i = 0;i < postHandCount;i++) {
    int card = testState->hand[player][i];
    if(card == copper || card == silver || card == gold) {
      postTreasureCount++;
    }
  }

  // deck and discard together lost 2 cards, which go to hand
  j_assert((preDeckCount + preDiscardCount - 2) == (postDeckCount + postDiscardCount));
  if((preDeckCount + preDiscardCount - 2) != (postDeckCount + postDiscardCount)) {
    printf("\n");
    printf("Pre Deck Count: %i\n", preDeckCount);
    printf("Pre Discard Count: %i\n", preDiscardCount);
    printf("Post Deck Count: %i\n", postDeckCount);
    printf("Post Discard Count: %i\n", postDiscardCount);
  }

  // hand grows by 2 cards
  j_assert((preHandCount + 2) == postHandCount);
  if((preHandCount + 2) != postHandCount) {
    printf("\n");
    printf("Pre Hand Count: %i\n", preHandCount);
    printf("Post Hand Count: %i\n", postHandCount);
  }

  // treasure in hand increases by 2
  j_assert((preTreasureCount + 2) == postTreasureCount);
  if((preTreasureCount + 2) != postTreasureCount) {
    printf("\n");
    printf("Pre Treasure Count: %i\n", preTreasureCount);
    printf("Post Treasure Count: %i\n", postTreasureCount);
  }
}

// random test generator
void random_tests() {
  struct gameState testState;

  // number of times random test run
  int i = 0;
  for(i = 0;i < RANDOM_RUNS;i++) {

    // randomize and test
    test_randomized_adventurer(&testState);
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
