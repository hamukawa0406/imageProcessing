#include "ifstream_string.h"

class binarization : public InctImage
{
private:
    int threshold;
public:
    RGBColor convert2Gray(RGBColor inPxl);
    void setThreshold(InctImage src);
    RGBColor convert2Bin(RGBColor inPxl);
};

class reduceNoise : public InctImage
{

};

class opening : public InctImage
{

};

class labeling : public InctImage
{

};