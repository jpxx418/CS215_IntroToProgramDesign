#ifndef PLAYINGCARD_H
#define	PLAYINGCARD_H
#include"globals.h"

using namespace std;

class PlayingCard
{
public:
    PlayingCard();
    int marks();
    void Card(int rank_value,int suit_num);
    void get_value(int);
    void get_suit(int);
    void get_string(char cardString[]);
    void changemark();
    
private:
    int rank_value;
    CardSuit suit;
    int mark;
};

#endif	/* PLAYINGCARD_H */

