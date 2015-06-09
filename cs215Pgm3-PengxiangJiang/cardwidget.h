#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>

class CardWidget: public QLabel
{  // Macro needed to handle signals and slots
   Q_OBJECT

public:
   CardWidget(char cardString[], int row, int column, QWidget *parent = 0);
   ~CardWidget();
   bool isHidden();
   bool isMatched();
   void unHide();
   void hide();
   void match();
   int getRow();
   int getColumn();

signals:
   void clicked(CardWidget*);

protected:
   virtual void mouseReleaseEvent(QMouseEvent *event);

private:
   char cardString[3];
   bool hidden;
   bool matched;
   void loadImage();
   int row;
   int column;

};

#endif
