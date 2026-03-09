// ***
// *** You MUST modify this file
// ***

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// do NOT modify this function
static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
    int origSize = origDeck.size;
    int divisions = origSize - 1;

    for (int i = 0; i < divisions; i++) 
    {
        int leftSize = i + 1;
        int rightSize = origDeck.size - leftSize;

        leftDeck[i].size = leftSize;
        rightDeck[i].size = rightSize;

        for (int j = 0; j < leftSize; j++) 
        {
            leftDeck[i].cards[j] = origDeck.cards[j];
        }

        for (int j = 0; j < rightSize; j++) 
        {
            rightDeck[i].cards[j] = origDeck.cards[leftSize + j];
        }
    }
}

void interleaveHelper(CardDeck leftDeck, CardDeck rightDeck, CardDeck resultDeck, int leftIndex, int rightIndex, int resultIndex, int round) {
    if (leftIndex == leftDeck.size) 
    {
        for (int i = rightIndex; i < rightDeck.size; i++) 
        {
            resultDeck.cards[resultIndex] = rightDeck.cards[i];
            resultIndex++;
        }
        
        if (round == 1) {
            printDeck(resultDeck);
        } else {
            shuffle(resultDeck, round - 1);
        }

        return;    
    } 
    else if (rightIndex == rightDeck.size) 
    {
        for (int i = leftIndex; i < leftDeck.size; i++) 
        {
            resultDeck.cards[resultIndex] = leftDeck.cards[i];
            resultIndex++; 
        }

        if (round == 1) {
            printDeck(resultDeck);
        } else {
            shuffle(resultDeck, round - 1);
        }

        return;
    }
    else {
        resultDeck.cards[resultIndex] = leftDeck.cards[leftIndex];
        interleaveHelper(leftDeck, rightDeck, resultDeck, leftIndex + 1, rightIndex, resultIndex + 1, round);

        resultDeck.cards[resultIndex] = rightDeck.cards[rightIndex];
        interleaveHelper(leftDeck, rightDeck, resultDeck, leftIndex, rightIndex + 1, resultIndex + 1, round);
    }        
}

void interleave(CardDeck leftDeck, CardDeck rightDeck, int round)
{
    CardDeck resultDeck;

    resultDeck.size = leftDeck.size + rightDeck.size;
    interleaveHelper(leftDeck, rightDeck, resultDeck, 0, 0, 0, round);
}

void shuffle(CardDeck origDeck, int round)
{
    int numPairs = origDeck.size - 1;

    CardDeck * leftDeck = malloc(sizeof(CardDeck) * numPairs);
    CardDeck * rightDeck = malloc(sizeof(CardDeck) * numPairs);

    divide(origDeck, leftDeck, rightDeck);

    for (int i = 0; i < numPairs; i++) {
        interleave(leftDeck[i], rightDeck[i], round);
    }

    free(leftDeck);
    free(rightDeck);
}
