#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QFrame>
#include <QGridLayout>

#include "cardwidget.h"

class CardWindow: public QFrame
{  // Macro needed to handle signals and slots
   Q_OBJECT

public:
   // Constructor
   CardWindow(QWidget *parent = 0);

private:
   void initializeCards();
   void createConnections();
   QGridLayout *layout;
   CardWidget *card1, *card2;

private slots:
   void handleClick(CardWidget *card);
};

#endif