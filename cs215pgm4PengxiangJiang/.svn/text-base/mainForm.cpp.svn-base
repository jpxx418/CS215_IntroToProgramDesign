/*
 * File:   mainForm.cpp
 * Author: Jeffrey
 *
 * Created on October 14, 2011, 1:39 PM
 */

#include <QFileDialog>
#include <QTextCodec>
#include "mainForm.h"
#include "globals.h"

bool loadImageFromFile(string filename);
void saveImageToFile(string filename);
image* displayImage();
void averageRegions(int blockWidth, int blockHeight);
void changeRedValues(int value);
void changeGreenValues(int value);
void changeBlueValues(int value);
void invertValues();

mainForm::mainForm() {
	widget.setupUi(this);
	connect(widget.pushButton_Open, SIGNAL(clicked()), this, SLOT(openFileDialog()));
	connect(widget.pushButton_Save, SIGNAL(clicked()), this, SLOT(saveFileDialog()));
	connect(widget.pushButton_Shrink, SIGNAL(clicked()), this, SLOT(shrinkImage()));
	connect(widget.pushButton_Red, SIGNAL(clicked()), this, SLOT(increaseRed()));
        connect(widget.pushButton_Red_Dec, SIGNAL(clicked()), this, SLOT(decreaseRed()));
	connect(widget.pushButton_Green, SIGNAL(clicked()), this, SLOT(increaseGreen()));
        connect(widget.pushButton_Green_Dec, SIGNAL(clicked()), this, SLOT(decreaseGreen()));
	connect(widget.pushButton_Blue, SIGNAL(clicked()), this, SLOT(increaseBlue()));
        connect(widget.pushButton_Blue_Dec, SIGNAL(clicked()), this, SLOT(decreaseBlue()));
	connect(widget.pushButton_Invert, SIGNAL(clicked()), this, SLOT(invertImage()));
	connect(widget.lineEdit_BlkWidth, SIGNAL(textChanged(QString)), this, SLOT(updateSizeInfo(QString)));
	InitializeComponent();

	// for system language other than English
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForCStrings(codec);
}

mainForm::~mainForm() {
}

void mainForm::InitializeComponent()
{
	origImageWidth = 0;
	origImageHeight = 0;
	blockHeight = 0;
	shrunk = false;
	
	widget.pushButton_Shrink->setDisabled(true);
	widget.pushButton_Red->setDisabled(true);
        widget.pushButton_Red_Dec->setDisabled(true);
	widget.pushButton_Green->setDisabled(true);
        widget.pushButton_Green_Dec->setDisabled(true);
	widget.pushButton_Blue->setDisabled(true);
        widget.pushButton_Blue_Dec->setDisabled(true);
	widget.pushButton_Invert->setDisabled(true);
	widget.pushButton_Save->setDisabled(true);
	widget.lineEdit_BlkWidth->setDisabled(true);
	widget.label_Image->setStyleSheet("QLabel { background-color : black;}");
}

void mainForm::openFileDialog()
{
	QString filename;

	if ((filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "" , tr("Image Files (*.jpg *.png *.bmp)"))) != "")  
	{
		if(!loadImageFromFile(filename.toStdString()))
			return;
		
		image* myImage = displayImage();
		
		if(myImage && myImage->getPixels())
		{
			widget.pushButton_Save->setDisabled(false);
			widget.label_BlkWidth->setDisabled(false);
			widget.pushButton_Red->setDisabled(false);
                        widget.pushButton_Red_Dec->setDisabled(false);
			widget.pushButton_Green->setDisabled(false);
                        widget.pushButton_Green_Dec->setDisabled(false);
			widget.pushButton_Blue->setDisabled(false);
                        widget.pushButton_Blue_Dec->setDisabled(false);
			widget.pushButton_Invert->setDisabled(false);
			widget.lineEdit_BlkWidth->setDisabled(false);
			
			char buffer[20];
			sprintf(buffer, "%d px", myImage->getHeight());			
			widget.label_height_Old->setText(QString(buffer));
		
			sprintf(buffer, "%d px", myImage->getWidth());
			widget.label_width_Old->setText(QString(buffer));

			this->origImageHeight = myImage->getHeight();
			this->origImageWidth = myImage->getWidth();

			if (int(myImage->getWidth()/100) > 0)
			{
				sprintf(buffer, "%d", myImage->getWidth()/100);
				widget.lineEdit_BlkWidth->setText(QString(buffer));
				setBlockWidth(myImage->getWidth()/100);
			}
			else
			{
				sprintf(buffer, "%d", 2);
				widget.lineEdit_BlkWidth->setText(QString(buffer));
				setBlockWidth(2);
			}
			
			this->shrunk = false;
			enableShrink();

			showImage(myImage);
		}
		else
		{
			cout << "The image could not be displayed because there is no pixel data!" << endl;
		}
	}
	
}

void mainForm::saveFileDialog()
{
	string filename;

	if ((filename = QFileDialog::getSaveFileName(this, tr("Save Image to File"), "", tr("Image Files (*.jpg *.png *.bmp)")).toStdString()) != "")  
	{
		saveImageToFile(filename);
	}
}

void mainForm::setBlockWidth(int width)
{
	int newWidth = int(this->origImageWidth/width);
	int height = width;
	if(!height)
		height = 1;
	this->blockHeight = height;
	int newHeight = int(this->origImageHeight/height);
	char buffer[20];
	sprintf(buffer, "%d px", newHeight);
	widget.label_height_New->setText(QString(buffer));
	
	sprintf(buffer, "%d px", newWidth);
	widget.label_width_New->setText(QString(buffer));
	
	sprintf(buffer, "%d px", height);
	widget.label_height_Blk->setText(QString(buffer));
}

void mainForm::disableShrink()
{
	widget.pushButton_Shrink->setDisabled(true);
	
	if(!this->shrunk)
	{
	   widget.label_height_New->setText("N/A");
	   widget.label_width_New->setText("N/A");
	   widget.label_height_Blk->setText("N/A");
	   widget.lineEdit_BlkWidth->setText("0");
	}
}

void mainForm::enableShrink()
{
   if(!this->shrunk)
		widget.pushButton_Shrink->setDisabled(false);
}

void mainForm::showImage(image* myImage)
{
	if(myImage->getPixels() && myImage->getHeight() && myImage->getWidth())
	{
		QImage out(myImage->getWidth(), myImage->getHeight(), QImage::Format_RGB32);
		myImage->viewImage(&out);
		widget.label_Image->setPixmap(QPixmap::fromImage(out));
	}
}

void mainForm::shrinkImage()
{
	bool ok;
	averageRegions(widget.lineEdit_BlkWidth->text().toInt(&ok, 10), this->blockHeight);
	this->shrunk = true;
	image* myImage = displayImage();
	if(myImage && myImage->getPixels())
	{
		widget.lineEdit_BlkWidth->setDisabled(true);
		disableShrink();
		showImage(myImage);
	}
	else
	{
		cout << "The image could not be displayed because there is no pixel data!" << endl;
	}	
}

void mainForm::increaseRed()
{
	changeRedValues(COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::increaseGreen()
{
	changeGreenValues(COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::increaseBlue()
{
	changeBlueValues(COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::decreaseRed()
{
	changeRedValues(-1 * COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::decreaseGreen()
{
	changeGreenValues(-1 * COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::decreaseBlue()
{
	changeBlueValues(-1 * COMPONENT_INCREASE_VALUE);
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::invertImage()
{
	invertValues();
	image* myImage = displayImage();
	
	if(myImage && myImage->getPixels())
		showImage(myImage);	
}

void mainForm::updateSizeInfo(QString newString)
{
	bool ok;
	int value = newString.toInt(&ok, 10);
	
	if(value && !this->shrunk)
	{
		if(value > this->origImageHeight)
			value = origImageHeight;
		if(value > this->origImageWidth)
			value = origImageWidth;
		char buffer[20];
		sprintf(buffer, "%d", value);
		widget.lineEdit_BlkWidth->setText(QString(buffer));

		setBlockWidth(value);
		enableShrink();
	}
	else
	{
		disableShrink();
	}	
}