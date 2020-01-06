#include "ifstream_string.h"
#include "statistic.h"
#include <map>

Statistic::Statistic(InctImage& _img):
    img{_img},
    Lut{}
{
    int count {};
    RGBColor trgb;
    sortedData.resize(img.getWidth()*img.getHeight());
    for(int j = 0; j < img.getHeight(); j++){
        for(int i = 0; i < img.getWidth(); i++){
            trgb = img.getPnmPixel(i, j);
            sortedData[count] = trgb.R;
            ++count;
        }
    }
    std::sort(sortedData.begin(), sortedData.end());
    setStatistic();
}

void Statistic::setStatistic(){
    double sum {};
    double powSum {};
    int count {};
    int cMax {};
    unsigned char _mode;
    for(auto x : sortedData){
        sum += x;
        powSum += pow(x, 2);
        if(x == _mode){
            ++count;
            _mode = x;
        }
        else if(count > cMax){
            mode = _mode;
        }
    }
    ave = calcAve(sum);
    var = calcVar(powSum);
    min = sortedData.front();
    max = sortedData.back();
    med = sortedData.at(sortedData.size() / 2);

}

double Statistic::calcAve(double sum){
    return sum / sortedData.size();
}

double Statistic::calcVar(double sum){
    return sum - pow(ave, 2);
} 

void Statistic::makeLUT(unsigned int kaichou){
	int k;
	static int i = 0;
	static int dosu = 0;
	static int ichikaichou = (int)(256 / kaichou);
	
	for(k = 0; k < 256; ++k){
		if(i < ichikaichou){
	        Lut[k] = dosu;
		    ++i;
		}
	    else{
		    dosu += ichikaichou;
		    i = 0;
		}
		
	}
}



void Statistic::setHist(){
    unsigned char preDens {0};
    makeLUT(hist.size());
    for(auto x = 0; x < sortedData.size(); ++x){
        sortedData[x] = Lut[sortedData[x]];
    }
    for(auto x = 1; x < sortedData.size(); ++x){
        if(preDens == sortedData[x]){

        }
    }
}


void Statistic::printHist(){

}
//*/
double Statistic::getAve(){
    return ave;
}
double Statistic::getVar(){
    return var;
}
double Statistic::getMax(){
    return max;
}
double Statistic::getMin(){
    return min;
}
double Statistic::getMed(){
    return med;
}

double Statistic::getMode(){
    return mode;
}


