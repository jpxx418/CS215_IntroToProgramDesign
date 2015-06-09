/*
 CS215Pgm5.cpp : main project file.  
 Author: Pengxiang Jiang 
 Completion Date: 
 
 This file should interface with the supplied Qt GUI interface to create photomosaics.
 Please read the included Project Specification for more detailed descriptions of the project.
 
 In this assignment we will be building on the work from Program 4 to create photomosaics.
 In the last assignment, we were able to break a photo up into smaller blocks and find the average color in each of those blocks.
 To create a photomosaic, we will further this idea by constructing a new image created from smaller images of the same average
 color as each of the blocks.
 
 Provided with the assignment is a folder of around 900 small 80x60 images.  These images are referred to as filler images.
 In the last assignment, you created a fillerImage class that extended the image class provided.  
 In this assignment we will start by reading in each of these small images into it's own fillerImage object.
 Each of these objects should be stored in a vector. 
 Note that you need to delete any dynamically allocated objects you have created when 
 the program closes.  Put this code in the programExiting() function.
 
 You should also extend your fillerImage class from Program 4 with the ability to store the number of times it has been used when
 creating the photomosaic.  Make this integer a private member of the class with getter and setter functions to access it.
 
 When loading in the filler images, you will be passed a string to a directory.  In this directory are images that are named
 a number followed by an extension.  You should open every image from FIRST_FILLER_NUMBER to LAST_FILLER_NUMBER.  These are global
 variables defined in globals.h.  Each file should therefore be of the name:  directory + "/" + number + FILLER_IMAGE_EXT.
 
 Once all of the filler images have been loaded, an image should be opened in the same manner as in Program 4.  Once this image
 is opened, the "Generate Mosaic" button can be pressed.  When pressed, a new image should be generated (much like in Program 4)
 but this time, instead of 1 pixel per block, each block will be represented by a new group of pixels FILLER_IMAGE_WIDTH by 
 FILLER_IMAGE_HEIGHT.
 
 The new image should consist of 1 filler image per block in the original image.  You should find the average color of the pixels in
 the block area and compare it to each of the filler images to produce a score.  The filler image with the lowest score should be used
 in the new image.  The metric to score a filler image is very similar to finding the euclidean distance between two 3D points.
 sqrt((blockAvg.red - fillerAvg.red)^2+(blockAvg.green - fillerAvg.green)^2+(blockAvg.blue - fillerAvg.blue)^2).
 This finds the image with the closest average color, however we also want to take into account the number of times we have already
 used the image.  If we have already used it several times before we want to penalize that image some.  Therefore the metric:
 sqrt((blockAvg.red - fillerAvg.red)^2+(blockAvg.green - fillerAvg.green)^2+(blockAvg.blue - fillerAvg.blue)^2)*(timesUsed+1)
 should provide a decent way to provide a score to each image.  Remember:  the image with the LOWEST score should be used!
 
 Now that we have selected a filler image to use, we need to apply a filter to the version of it that we will be using in the final
 image.  Because often the filler image selected will not have an average color that is completely like the original image block, we
 will apply a filter to adjust the RGB tint of the filler image used (like in Program 4).  You should copy all the pixels of the filler
 image to the appropriate location in the newly created image, with each pixel modified so that the red component is increased or decreased
 an amount corresponding to blockAvg.red - fillerAvg.red.  This should also be done for the green and blue components.  So once you have the
 average pixel colors for the image block and the filler image, find the difference between each component and add/subtract that difference
 to each pixel of the copied filler image. (REMEMBER: you MUST make sure the values stay between 0 and 255!  If a value goes negative, set
 it to 0.  Greater than 255, set it to 255.)
 
 Performance Analysis:
 We need to collect data to analyze the performance of two characteristics of the program
 1. Collect the time needed to generate mosaics using same base image and set of fillers
 using different block widths, like 10,11,12,.... Plot the time as a function of block area.
 2. Collect the average time of searching for the best icon for each block width as described above.
 Plot the average time as function of block area.
 Note: You can use other software to plot the diagram like Matlab or Excel.
 
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
 If a user has used the Generate Mosaic button, you should of course return a pointer to an image object that 
 reflects these changes.
 
 bool loadFillerImagesFromFolder(string folder)
 INPUTS:  a string containing a path to a directory containing all of the filler images.
 OUTPUTS:  A boolean indicating if all the images loaded correctly into the vector or not
 
 void programExiting()
 INPUTS:  NONE
 OUTPUTS:  NONE
 You should call your dynamic memory deletion code in here.
 
 bool imageLoaded()
 INPUTS:  NONE
 OUTPUTS:  a boolean indicating whether a base image has been loaded successfully.
 
 void generateMosaic(int blockWidth, int blockHeight)
 INPUTS:  Integers indicating the width and height of the â€œblocksâ€?to be averaged
 OUTPUTS: NONE
 Generate the Mosaic as described above.
 
 fillerImage* findBestFillerImage(pixel color)
 INPUTS: A pixel object indicating the average color of the image block to be matched by a filler image.
 OUTPUTS: A pointer to a filler image object (remember, these objects are going to be stored in an STL list) which is the result of the metric Distance-2 being applied to all the filler image objects in the STL list.  The returned pointer is a pointer to the filler image object with the minimum score using the metric.
 This function is a helper function, and should be invoked by generateMosaic().
 
 */

#include <cstdlib>
#include <list>
#include <iostream>
#include <sstream>
#include <math.h>
#include <time.h>


#include "globals.h"		//some global variables are included here
#include "pixel.h"			//includes the pixel class for storing individual pixels
#include "image.h"			//includes the image class we will be using.
#include "fillerImage.h"	//include the fillerImage class that is implemented by you

using namespace std;


//declare your global variables here!
list<fillerImage*> myImage;
list<fillerImage*> mosaic;
image* BasicImage = new image;
image* NewImage = new image;
image* Display = BasicImage;
pixel blockave;



//load the filler images from the given folder into a vector of fillerImage.
bool loadFillerImagesFromFolder(string folder) 
{
    for(int i = FIRST_FILLER_NUMBER; i <= LAST_FILLER_NUMBER; i++)
    {
        fillerImage* Filler = new fillerImage;
        ostringstream location;
        location << folder << "/" << i << FILLER_IMAGE_EXT;
        string filename = location.str();
        if(Filler ->loadImage(filename))
        {
            Filler ->calculateAverageColor();
            myImage.push_back(Filler);
        }
        else
            return false;
    }
    return true;
}



//This function is called when the program is closing.  Make sure to delete any dynamically allocated memory here!
void programExiting()
{
    for (list<fillerImage*>::iterator iter = myImage.begin(); iter != myImage.end(); iter++)
        delete (*iter);
    
    for (list<fillerImage*>::iterator iter = mosaic.begin(); iter != mosaic.end(); iter++)
        delete (*iter);
    myImage.clear();
    mosaic.clear();
}



//This function should return true if an image has been successfully loaded to turn into a mosaic, and false if one has not.
bool imageLoaded() 
{
    if(BasicImage != NULL)
        return true;
    else
        return false;
}



//Tinting the filler
fillerImage* Tint(pixel color, fillerImage* myImage)
{
    int redDistance = blockave.red - myImage->getAve().red;
    int greenDistance = blockave.green - myImage->getAve().green;
    int blueDistance = blockave.blue - myImage->getAve().blue;
    fillerImage* myfiller = new fillerImage();
    myfiller->createNewImage(myImage->getWidth(), myImage->getHeight());
    pixel** oldPixels = myImage->getPixels();
    pixel** newPixels = myfiller->getPixels();
    for (int i = 0; i < FILLER_IMAGE_HEIGHT; i ++)
        for (int j = 0; j < FILLER_IMAGE_WIDTH; j ++)
        {
            int R = oldPixels[i][j].red + redDistance;
            int B = oldPixels[i][j].blue + blueDistance;
            int G = oldPixels[i][j].green + greenDistance;
            if ( R < 0)
                R = 0;
            else if (R > 255)
                R = 255;
            if (B < 0)
                B = 0;
            else if (B > 255)
                B = 255;
            if (G < 0)
                G = 0;
            else if (G > 255)
                G = 255;
            newPixels[i][j].red = R;
            newPixels[i][j].blue = B;
            newPixels[i][j].green = G;
        }
    return myfiller;
}



void GenerateNewImage(int blockHeight ,int blockWidth , pixel**npix )
{
    int numBlocksCol = BasicImage->getHeight() / blockHeight;
    int numBlocksRow = BasicImage->getWidth() / blockWidth;
    list<fillerImage*>::iterator it = mosaic.begin();
    for(int i =0;i < numBlocksCol;i++)
    {
        for(int j = 0;j < numBlocksRow; j++)
        {
            int y = j*FILLER_IMAGE_WIDTH;
            int x = i*FILLER_IMAGE_HEIGHT;
            for(int n = 0;n < FILLER_IMAGE_WIDTH; n++)
            {
                for(int m = 0;m < FILLER_IMAGE_HEIGHT; m++)
                {
                    pixel **copypixels = (*it)->getPixels();
                    
                    npix[x + m][y + n] = copypixels[m][n];
                }
            }
            it++;
        }
    }
    Display = NewImage;
}



//This function is a helper function, and should be invoked by generateMosaic().
fillerImage* findBestFillerImage(pixel color)
{
    list<fillerImage*>::iterator it = myImage.begin();
    fillerImage* theMatch = (*it);
    int redDistance = blockave.red - (*it)->getAve().red;
    int greenDistance = blockave.green - (*it)->getAve().green;
    int blueDistance = blockave.blue -(*it)->getAve().blue;
    int t = (*it)->gettimes();
    double mindistance = 10000;
    double temp;
    for (int n = FIRST_FILLER_NUMBER; n < LAST_FILLER_NUMBER; n++)
    {
        redDistance = blockave.red - (*it)->getAve().red;
        greenDistance = blockave.green - (*it)->getAve().green;
        blueDistance = blockave.blue - (*it)->getAve().blue;
        t = (*it)->gettimes();
        temp = sqrt(pow((double)redDistance,2) + pow((double)greenDistance,2) + pow((double)blueDistance,2))*(t+1);
        if(temp < mindistance)
        {
            mindistance  = temp;
            theMatch = (*it);
        }
        
        it++;
    }
    return theMatch;
}



//This function should generate the photomosaic from the loaded image.  Each filler image should represent a section of the original image
//that is blockWidth by blockHeight big.
void generateMosaic(int blockWidth, int blockHeight) 
{
    int count = 0;
    clock_t start1, end1;
    clock_t start2, end2;
    double passed1;
    double passed2;
    for (list<fillerImage*>::iterator it = mosaic.begin(); it != mosaic.end(); it++)
        delete (*it);
    mosaic.clear();
    int numBlocksCol = BasicImage->getHeight() / blockHeight;
    int numBlocksRow = BasicImage->getWidth() / blockWidth;
    NewImage->createNewImage(numBlocksRow * FILLER_IMAGE_WIDTH, numBlocksCol * FILLER_IMAGE_HEIGHT);
    pixel** pix = BasicImage->getPixels();
    pixel** npix = NewImage->getPixels();
    start1 = clock();
    for(int i = 0; i < numBlocksCol; i++)
    {
        for(int j = 0; j < numBlocksRow; j++)
        {
            int red = 0, blue = 0 ,green = 0;
            for(int m = 0;m < blockHeight;m++)
            {
                for(int n = 0; n < blockWidth;n++)
                {
                    red += pix[i*blockHeight + m][j*blockWidth + n].red;
                    green += pix[i*blockHeight + m][j*blockWidth + n].green;
                    blue += pix[i*blockHeight + m][j*blockWidth + n].blue;
                }
            }
            blockave.red = red / (blockHeight * blockWidth);
            blockave.green = green / (blockHeight * blockWidth);
            blockave.blue = blue / (blockHeight * blockWidth);
            start2 = clock();
            fillerImage* Matchfiller = findBestFillerImage(blockave);
            end2 = clock();
            count++;
            passed2 += ((double) (end2 - start2)) / CLOCKS_PER_SEC;
            Matchfiller->settimes();
            Matchfiller = Tint(blockave, Matchfiller);
            mosaic.push_back(Matchfiller);
        }
    }
    GenerateNewImage(blockHeight, blockWidth, npix );
    end1 = clock();
    passed1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    cout << "The time of building a mosaic image :" << passed1 << endl;
    cout << "The average time of searching for the best icon :" << passed2 / count <<endl;
}



//load the image from a file and return the result
bool loadImageFromFile(string filename) 
{
    bool value = BasicImage->loadImage(filename);
    Display = BasicImage;
    return value;
}

//save an image to a file
void saveImageToFile(string filename) 
{
    Display->saveImage(filename);
}

//return a pointer to your image object!
image* displayImage() 
{
    return Display;
}