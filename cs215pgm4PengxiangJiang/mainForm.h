/* 
 * File:   mainForm.h
 * Author: Jeffrey
 *
 * Created on October 14, 2011, 1:39 PM
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "ui_mainForm.h"
#include <iostream>
#include "image.h"
#include "globals.h"

using namespace std;

class mainForm : public QDialog {
	Q_OBJECT
public:
	mainForm();
	void InitializeComponent();
	virtual ~mainForm();
	
private:
	Ui::mainForm widget;
	int origImageWidth;
	int origImageHeight;
	int blockHeight;
	bool shrunk;
	
	void setBlockWidth(int width);
	void disableShrink();
	void enableShrink();
	void showImage(image* myImage);
	
public slots:
         void openFileDialog();
	 void saveFileDialog();
	 void shrinkImage();
	 void increaseRed();
	 void increaseBlue();
	 void increaseGreen();
         void decreaseRed();
         void decreaseGreen();
         void decreaseBlue();
	 void invertImage();
	 void updateSizeInfo(QString newString);
};

#endif	/* _MAINFORM_H */

