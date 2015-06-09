#include <QMessageBox>
#include <QMouseEvent>
#include <QString>
#include <QSizePolicy>

#include "cardwidget.h"
#include "globals.h"

// Constructor
CardWidget::CardWidget(char cardString[], int row, int column, QWidget* parent)
   :QLabel(parent)
{  this->cardString[0] = cardString[0];
   this->cardString[1] = cardString[1];
   this->cardString[2] = cardString[2];
   this->row = row;
   this->column = column;

   setBackgroundRole(QPalette::Base);

   // Don't let our cards get any bigger
   setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
   setScaledContents(true);

   // Set default values
   hidden = true;
   matched = false;
   loadImage();
}

// Destructor
CardWidget::~CardWidget()
{
}

// Accessors
bool CardWidget::isMatched()
{  return matched;
}

bool CardWidget::isHidden()
{  return hidden;
}

int CardWidget::getRow()
{  return row;
}

int CardWidget::getColumn()
{  return column;
}

// Mutators
void CardWidget::unHide()
{  hidden = false;
   loadImage();
}

void CardWidget::hide()
{  hidden = true;
   loadImage();
}

void CardWidget::match()
{  matched = true;
   loadImage();
}

// Loads the correct image based on the situation
void CardWidget::loadImage()
{  QString filename;
   if(isHidden())
   {  filename = ":/back.png";
   }
   else if(isMatched())
   {  filename = ":/check.png";
   }
   else
   {  filename = QString(":/%1.png").arg(cardString);
   }
   QImage image(filename);

   if(image.isNull())
   {  QMessageBox::information(this,tr("Error"),
                               tr("Cannot load image %1.").arg(cardString));
      return;
   }
   this->setPixmap(QPixmap::fromImage(image));
   resize(pixmap()->size());
}

// Emit a signal when clicked
void CardWidget::mouseReleaseEvent(QMouseEvent *event)
{  if(event->button() == Qt::LeftButton)
   {  emit clicked(this);
   }
}
