#include "ifstream_string.h"

class Statistic
{
private:
    InctImage img;
    double ave;
    double var;
    double max;
    double min;
    double med;
    double mode;
    double hist[8];
    double calcAve();
    double calcVar();
    double calcMax();
    double calcMin();
    double calcMed();
    double calcMode();
    void setHist();
public:
    Statistic(InctImage);
    double getAve();
    double getVar();
    double getMax();
    double getMin();
    double getMed();
    double getMode();
    void printHist();
};