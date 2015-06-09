#include <QGridLayout>
#include <QMessageBox>

#include "cardwindow.h"
#include "cardwidget.h"
#include "globals.h"

void getCard(int row, int column, char cardString[]);
void shuffleCards();
void matchTwoCards(int row1, int column1, int row2, int column2);
bool isCardMatched (int row, int column);
bool isGameOver();

// Constructor
CardWindow::CardWindow(QWidget *parent)
   : QFrame(parent)
{  // Set default values
   card1 = NULL;
   card2 = NULL;

   // Set up frame
   setWindowTitle(tr("Card Game"));
   layout = new QGridLayout(this);
   setLayout(layout);
   initializeCards();
   // Don't let us resize the window
   setMaximumSize(minimumSize());

}

void CardWindow::initializeCards()
{  // Shuffle deck
   shuffleCards();

   // This assumes the enum values are the defaults
   // WTB c++0x enum classes
   CardWidget *card;
   char buffer[3] = {'\0','\0','\0'};
   for(int s=0; s<SUITS_NUM; s++)
   {  for(int v=0; v<2*RANKS_NUM; v++)
      {  // Add the next card to the window
         getCard(s,v, buffer);
         card = new CardWidget(buffer,s,v);
         layout->addWidget(card,s,v);

         // Setup signal/slot connection to each card
         connect(card, SIGNAL(clicked(CardWidget*)),
                 this, SLOT(handleClick(CardWidget*)));
      }
   }
}

void CardWindow::handleClick(CardWidget *card)
{  // Hide the previous cards
   if(card1 != NULL && card2 != NULL)
   {  if(!isCardMatched(card1->getRow(),card1->getColumn()))
      {  card1->hide();
         card2->hide();
      }
      else
      {  card1->match();
         card2->match();
      }
      card1 = NULL;
      card2 = NULL;
   }

   // Ignore the click if the card has been matched or
   // is already face up
   if(isCardMatched(card->getRow(),card->getColumn()) ||
         !card->isHidden())
   {  return;
   }

   // Track the two clicked cards
   if(card1 == NULL)
   {  card->unHide();
      card1 = card;
      return;
   }
   card2 = card;
   card2->unHide();

   // Compare the cards
   matchTwoCards(card1->getRow(), card1->getColumn(),
              card2->getRow(), card2->getColumn());
   if(isGameOver())
   {  QMessageBox msgBox;
      msgBox.setText("Congratulations!\n\nYou matched all the cards!!!");
      msgBox.exec();
      this->close();
   }
}
