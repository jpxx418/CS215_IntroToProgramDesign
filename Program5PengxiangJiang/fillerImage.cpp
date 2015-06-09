#include "fillerImage.h"

// implement your functions here

using namespace std;

fillerImage::fillerImage()
{
    times = 0;
    AveColor.red = 0;
    AveColor.green = 0;
    AveColor.blue = 0;
}

pixel fillerImage::getAve()
{
    return AveColor;
}

void fillerImage::calculateAverageColor()
{
    int red = 0;
    int green = 0;
    int blue = 0;
    pixel **pixels = getPixels();
    for(int i=0; i< getHeight(); i++)
    {
        for(int j=0; j< getWidth(); j++)
        {
            red += pixels[i][j].red;
            green += pixels[i][j].green;
            blue += pixels[i][j].blue;
        }
    }
    //calculate the average color
    red/= (getHeight()*getWidth());
    green/= (getHeight()*getWidth());
    blue/= (getHeight()*getWidth());
    
    AveColor.red = red;
    AveColor.green = green;
    AveColor.blue = blue;
}

int fillerImage::gettimes()
{
    return times;
}

void fillerImage::settimes()
{
    times++;
}
