#include<iostream>
#include<array>
#include<algorithm>
#include "ifstream_string.h"


class Statistic
{
private:
    InctImage& img;
    std::vector<unsigned char> sortedData;
    double ave;
    double var;
    double max;
    double min;
    double med;
    double mode;
    unsigned char Lut[256];
    std::array<int, 8> hist;
    void setStatistic();
    double calcAve(double sum);
    double calcVar(double sum);
    void makeLUT(unsigned int kaichou);
    void setHist();
public:
    Statistic();
    Statistic(InctImage & _img);
    double getAve();
    double getVar();
    double getMax();
    double getMin();
    double getMed();
    double getMode();
    void printHist();
};