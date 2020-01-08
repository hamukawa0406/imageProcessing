#include<iostream>
#include<array>
#include<algorithm>
#include "ifstream_string.h"


class Statistic
{
private:
    InctImage& img;
    std::string outname;
    std::ofstream writing_file;
    std::vector<unsigned char> sortedData;
    double ave;
    double var;
    double max;
    double min;
    double med;
    double mode;
    std::array<int, 32> hist;
    void setStatistic();
    double calcAve(double sum);
    double calcVar(double sum);
    void setHist();
public:
    Statistic(InctImage & _img);
    double getAve();
    double getVar();
    double getMax();
    double getMin();
    double getMed();
    double getMode();
    void printHist();
    void outputStatistic();
};