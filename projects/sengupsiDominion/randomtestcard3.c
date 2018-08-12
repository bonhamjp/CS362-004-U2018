/***********************************
 * Sidharth Sengupta
 * Random Test 2 for Assignment 4
 * Tests the great hall card
 ************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NUMTRIES 100

int asserttrue(int a, int b, char *error) {

    if(a != b) {
        printf("%s\n", error);
        return 0;
    }   
    return 1;
}

int main() {

    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int x, i, j;  
    int p, size, top;
	srand(time(0));


    printf("Random Card Test 3: Testing Great Hall\n");

	for(i = 0; i < NUMTRIES; i++) {

        printf("Iteration %d\n", i + 1);
		initializeGame(numPlayer, k, seed, &G);
		p = rand() % 2;
		G.whoseTurn = p;

		if(p != 0) {		
			for (j = 0; j < 5; j++)
				drawCard(G.whoseTurn, &G);
		}
		x = 1;
	
        G.deckCount[p] = size = (rand() % 9) + 2;

        for(j = 0; j < size; j++) 
			G.deck[p][j] = k[rand() % 10];

		top = G.deck[p][size - 1];

		G.hand[p][0] = great_hall;
		playCard(0, 0, 0, 0, &G);

        if(asserttrue(5, G.handCount[p], "Hand Count Failed") == 0 && x != 0)
            x = 0;
        if(asserttrue(top, G.hand[p][0], "Top Card Failed") == 0 && x != 0)
            x = 0;
        if(asserttrue(1, G.numActions, "Num Actions Failed") == 0 && x != 0)
            x = 0;

		if(x)
            printf("Random Card Test 3 Iteration %d Successfully Completed\n\n", i + 1); 
        else {
            printf("Random Card Test 3 Iteration %d Failed\n", i + 1); 
            printf("Expected hand count: 5, actual: %d\n", G.handCount[p]);
            printf("Expected top card: %d, actual: %d\n", top, G.hand[p][0]);
            printf("Expected num actions: 1, actual: %d\n\n", G.numActions);
		}   
    }   
    return 0;
}
