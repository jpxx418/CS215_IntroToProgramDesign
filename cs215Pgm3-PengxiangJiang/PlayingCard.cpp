#include "globals.h"
#include "PlayingCard.h"

using namespace std;
    
 void PlayingCard::get_value(int i)
{
    rank_value = i;
}

 void PlayingCard::get_suit(int i)
{
    if (i == 0)
                suit = SPADE;
    else if (i == 1)
                suit = HEART;
    else if (i == 2)
                suit = DIAMOND;
    else if (i == 3)
                suit = CLUB;
}

void PlayingCard::Card(int rank_value,int suit_num)
{
    get_value(rank_value);
    get_suit(suit_num);
}

void PlayingCard::get_string(char cardString[])
{
    	if(suit == SPADE)
		cardString[0] = 'S';
	else if(suit == CLUB)
		cardString[0] = 'C';
	else if(suit == HEART)
		cardString[0] = 'H';
	else if(suit == DIAMOND)
		cardString[0] = 'D';

	char value;

	if(rank_value == 0)
		value = '9';
	else if(rank_value == 1)
		value = 'T';
	else if(rank_value == 2)
		value = 'J';
	else if(rank_value == 3)
		value = 'Q';
        else if(rank_value == 4)
                value = 'K';
        else if(rank_value == 5)
		value = 'A';
	cardString[1] = value;
	cardString[2] = '\0';
}


 PlayingCard::PlayingCard()
    {
        rank_value = 0;
        suit = SPADE;
        mark = 0;
    }

void PlayingCard::changemark()
{
    mark = 1;
}   

int PlayingCard::marks()
{
   return mark;
}