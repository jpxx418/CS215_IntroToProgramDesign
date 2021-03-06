
/*
 * v2.1
	CS215Pgm4.cpp : main project file.  
	Author: Pengxiang Jiang 
	Completion Date: April 14, 2012

	This file should interface with the supplied windows GUI interface to allow images to be resampled to smaller sizes and be tinted.
	Please read the included Project Specification for more detailed descriptions of the project.

	In this assignment, we will be laying the foundation for a larger photo-mosiac project.  
	We will be finding the average color in a larger block of pixels (aka re-sampling).  
	This technique is often used to generate smaller versions of big images.  (think of a thumbnail of the original image)  
	
	In this assignment we will be writing a program that can:

	1.)Allow simple loading and saving of images.
	2.)Break a loaded image up into blocks of a given width and height and find the average color in that block.
	3.)Create a new image from the process in 2 that will consist of 1 pixel per every block analyzed in the first image.
	4.)Apply a red, green, or blue tint to an image by increasing the appropriate RGB values to every pixel in the image.
	5.)Invert the individual RGB color components of an image.



	The functions in this file should be completed as follows:

bool loadImageFromFile(string filename)
		INPUTS: a string containing a path to a file to open.  This value is returned from the 
		user's selection in the open file dialog.
		OUTPUTS: a boolean indicating whether or not the image could be opened correctly.

void saveImageToFile(string filename)
		INPUTS: a string containing a path to save the current image out to.
		OUTPUTS: NONE

image* displayImage()
		INPUTS: NONE
		OUTPUTS: This function should return a pointer to the image object that is currently being viewed on the screen.  
		If a user has loaded an image correctly, you should return a pointer to an image object containing the base image.  
		If a user has used the shrink button (aka averageRegions function) or performed any of the red/green/blue filters, 
		you should of course return a pointer to an image object that reflects these changes.

void averageRegions(int blockWidth, int blockHeight)
		INPUTS: Integers indicating the width and height of the "blocks" to be averaged
		OUTPUTS: NONE
		When this function is called, you should create a new image that will consist of 1 pixel for every block of size 
		blockWidth by blockHeight pixels in the original image, with each pixel being the average color of the pixels in that 
		region in the original image.
		Please note that it may be easier if you split this into 2 functions and call your helper function from within this one.  
		The second function could then just calculate the average value of a block of pixels given to it, and return that 
		to the original function to be used.  However, this implementation is up to you!  Complete it as you see fit.

void changeRedValues(int value)
		INPUTS: An integer indicating the amount to increase/decrease the red component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and add the red component of each 
		pixel in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.

void changeGreenValues(int value)
		INPUTS: An integer indicating the amount to increase/decrease the green component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and add the green component of each pixel 
		in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.

void changeBlueValues(int value)
		INPUTS: An integer indicating the amount to increase/decrease the blue component of each pixel.
		OUTPUTS: NONE
		When this function is called, you should take the current image and add the blue component of each pixel
		in the image by the amount specified.  Please note that an RGB value has a maximum of 255 and a minimum of 0.

void invertValues()
		INPUTS: NONE
		OUTPUTS: NONE
		When this function is called you should "invert" all the individual components of each pixel in the current image.  
		To invert a pixel, simply set each component in the pixel to it's maximum value (255) minus it's current value.  
		So if the red component of a pixel to be inverted was 25, it should now be 230.  Repeat this process for every 
		component of every pixel in the image.
*/

#include <cstdlib>
#include <string>

using namespace std;

#include "globals.h"  //some global variables are included here
#include "pixel.h"  //includes the pixel class for storing individual pixels
#include "image.h"	//includes the image class we will be using.
 
//declare your global variables here!
image oldImage;
image changedImage;
image *newImage = &oldImage;


//load the image from a file and return the result
bool loadImageFromFile(string filename)
{
	bool boolean = oldImage.loadImage(filename);
        newImage = &oldImage;
	return boolean;
}


//save an image to a file
void saveImageToFile(string filename)
{
	newImage->saveImage(filename);
}


//return a pointer to your image object!
image* displayImage()
{
	return newImage;
}


//make a new image that is a smaller resampling of the bigger image
void averageRegions(int blockWidth, int blockHeight)
{
    int numBlocksCol = oldImage.getWidth() / blockWidth;
    int numBlocksRow = oldImage.getHeight() / blockHeight;
    changedImage.createNewImage(numBlocksCol,numBlocksRow);
    pixel **pixels = oldImage.getPixels();
    pixel **newpixels = changedImage.getPixels();
    for(int i =0; i<numBlocksRow; i++)
    {
        for(int j =0;j<numBlocksCol;j++)
        {
            int red =0,blue =0 ,green=0;
            for(int m=0;m < blockHeight;m++)
            {
                for(int n =0; n < blockWidth;n++)
                {
                    red += pixels[i * blockHeight + m][j * blockWidth + n].red;
                    green += pixels[i * blockHeight + m][j * blockWidth + n].green;
                    blue += pixels[i * blockHeight + m][j * blockWidth + n].blue;
                }
            }

            newpixels[i][j].red =uchar( red /(blockWidth * blockHeight));
            newpixels[i][j].green = uchar(green/(blockWidth * blockHeight));
            newpixels[i][j].blue = uchar(blue/(blockWidth * blockHeight));
        }
    }
    if(newImage!=&oldImage)
    {
        delete newImage;
    }
    newImage = &changedImage;
}


//change the red component of each pixel in the image
void changeRedValues(int value)
{
	pixel **buf = newImage->getPixels();
	for(int i = 0; i < newImage->getHeight();i++)
	{
		for(int j = 0; j < newImage->getWidth(); j++)
		{
			int val = buf[i][j].red + value;
                        if(val > 255) 
                        {
                            val = 255;
                        } 
                        else if(val < 0) 
                        {
                            val = 0;
                        }
                     buf[i][j].red = val;
		}
	}	
        
}


//change the green component of each pixel in the image
void changeGreenValues(int value)
{
	pixel **buf = newImage->getPixels();
	for(int i = 0; i < newImage->getHeight();i++)
	{
		for(int j = 0; j < newImage->getWidth(); j++)
		{
			int val = buf[i][j].green + value;
                        if(val > 255) 
                        {
                            val = 255;
                        } 
                        else if(val < 0) 
                        {
                            val = 0;
                        }
                     buf[i][j].green = val;
		}
	}	
}


//change the blue component of each pixel in the image
void changeBlueValues(int value)
{
	pixel **buf = newImage->getPixels();
	for(int i = 0; i < newImage->getHeight();i++)
	{
		for(int j = 0; j < newImage->getWidth(); j++)
		{
			int val = buf[i][j].blue + value;
                        if(val > 255) 
                        {
                            val = 255;
                        } 
                        else if(val < 0) 
                        {
                            val = 0;
                        }
                     buf[i][j].blue = val;
		}
	}	
}


//invert the color components of each pixel in the image
void invertValues()
{
	pixel **buf = newImage->getPixels();
	for(int i = 0;i < newImage->getHeight();i++)
	{
		for(int j = 0; j < newImage->getWidth(); j++)
		{
			buf[i][j].red = 255-buf[i][j].red;
			buf[i][j].green = 255-buf[i][j].green;	
			buf[i][j].blue = 255-buf[i][j].blue;
		}
	}	
}
