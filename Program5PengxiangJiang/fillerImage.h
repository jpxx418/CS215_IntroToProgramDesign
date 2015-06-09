
#ifndef FILLER_IMAGE
#define FILLER_IMAGE

#include "globals.h"
#include "image.h"

class fillerImage : public image {
public:
    // add your functions here
    fillerImage();
    pixel getAve();
    void calculateAverageColor();
    int gettimes();
    void settimes();
private:
    // add your private variables here
    pixel AveColor;
    int times;
};

#endif

