#include <ctime>
#include<cstdlib>
#include<time.h>
#include "PlayingCard.h"
#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck()
{
        for(int i = 0;i < SUITS_NUM;i++)
        {
            for(int j = 0;j < RANKS_NUM;j++)
            {
                Deck[i][j].Card(j,i);
            }
            for(int j = 0;j < RANKS_NUM;j++)
            {
                Deck[i][j + RANKS_NUM].Card(j,i);
            }
        }
}

PlayingCard CardDeck::get_card(int row,int column)
{
    return Deck[row][column];
}

void CardDeck::changemark2(int row,int column)
    {
           Deck[row][column].changemark();
    }

int CardDeck::marks2(int row,int column)
    {
          return Deck[row][column].marks();
    }

void CardDeck::shufflecard()
{
    srand(time(NULL));
    for (int i = 0; i < SHUFFLE_RANDOM_SWITCHES;i++)
    {
        int Row1 = rand()%SUITS_NUM;
        int Row2 = rand()%SUITS_NUM;
        int Col1 = rand()%(2 * RANKS_NUM);
        int Col2 = rand()%(2 * RANKS_NUM);

        PlayingCard tmpCard = Deck[Row1][Col1];
        Deck[Row1][Col1] = Deck[Row2][Col2];
        Deck[Row2][Col2] = tmpCard;
    }
}


