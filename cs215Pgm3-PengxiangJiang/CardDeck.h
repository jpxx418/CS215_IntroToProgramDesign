#ifndef CARDDECK_H
#define	CARDDECK_H
#include"PlayingCard.h"
using namespace std;
class CardDeck
{
public:
    CardDeck();
    PlayingCard get_card(int row,int column);
    void changemark2(int row,int column);
    int marks2(int row,int column);
    void shufflecard();

private:
    PlayingCard Deck[SUITS_NUM][2*RANKS_NUM];
};


#endif	/* CARDDECK_H */

