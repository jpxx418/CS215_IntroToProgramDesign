#ifndef GLOBALS_H
#define GLOBALS_H
//v1.2
// This file contains some global variables used in the rest of the code.

// This is an enum type that indicates the kinds of suits available in the deck 
// of cards. After declaring this enum type, we can create a cardSuit variable 
// that can take the values of
// SPADE, CLUB, HEART, or DIAMOND.  For example:
// CardSuit mySuit;
// mySuit = CLUB;
// This would set mySuit to CLUB.
enum CardSuit {CLUB, DIAMOND, HEART, SPADE};

// This is an enum type that indicates the kinds of ranks available in the deck
// of cards. Usage is analogous to the CardSuit enum.
enum CardRank {NINE, TEN, JACK, QUEEN, KING, ACE};

// This is the number of different suits (usually 4)
const int SUITS_NUM = 4;

// This is the number of individual values that a card can have
// (6 for a skat or half pinochle deck)
const int RANKS_NUM = 6;  

// This is the number of times that a pair of cards is switched in the 
// shuffle function.
const int SHUFFLE_RANDOM_SWITCHES = 25;  

#endif