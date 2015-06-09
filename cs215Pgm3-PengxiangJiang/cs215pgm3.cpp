#include<iostream>
#include<cstring>
#include <ctime>
#include <cstdlib>
#include "CardDeck.h"
#include "PlayingCard.h"
#include "globals.h"

using namespace std;

PlayingCard myCard;
CardDeck myDeck;

 void getCard(int row, int column,char cardString[])
{       
    myCard=myDeck.get_card(row,column);
    myCard.get_string(cardString);
}

void shuffleCards()
{
    myDeck.shufflecard();
}

void matchTwoCards(int row1, int column1, int row2, int column2)
{
    bool isCardMatched(int row, int column);
    void getCard(int row, int column,char cardString[]);
    char string1[3],string2[3];
    getCard(row1,column1,string1);
    getCard(row2,column2,string2);
    if(strcmp (string1,string2) == 0)
    {
        myDeck.changemark2(row1,column1);
        myDeck.changemark2(row2,column2);
    }
}

bool isCardMatched(int row, int column)
{
    if(myDeck.marks2(row,column)) return true;
    else  return false;
}

bool isGameOver()
{
    for(int i=0;i<SUITS_NUM;i++)
   {
        for(int j=0;j<RANKS_NUM;j++)
        {
            if(myDeck.marks2(i,j)==0)
                return false;
        }
    }
    return true;
}

