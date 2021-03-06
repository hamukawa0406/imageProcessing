#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset>
#include <map>

using namespace std;

#define MODE_ASCII_GRAY 1
#define MODE_ASCII_COLOR 3
#define MODE_BINARY_GRAY 4
#define MODE_BINARY_COLOR 5

struct PnmHeader{
	string Pnum;
	string Width;
	string Height;
	string Depth;
	string Com[4];
};

class RGBColor{
public:
	union {
		struct {
			unsigned char R,G,B;
		};
		unsigned char Dens;
		unsigned char Bit:1;//めんどいから使ってないw
	};

	RGBColor(unsigned char _r,unsigned char _g,unsigned char _b)
	{
		R = _r;G = _g;B = _b;
	}
	RGBColor()
	{
		R = 0;G = 0;B = 0;
	}
	unsigned char getR() const {return R;}
	unsigned char getG() const {return G;}
	unsigned char getB() const {return B;}
	unsigned char getDens() const {return Dens;}
	void setR(unsigned char _r){R=_r;}
	void setG(unsigned char _g){G=_g;}
	void setB(unsigned char _b){B=_b;}
	void setDens(unsigned char _dens){Dens=_dens;}
	void setRGB(unsigned char _r,unsigned char _g,unsigned char _b){R=_r;G=_g;B=_b;}
	void setBit(unsigned char _bit){}
};


	enum RGB{
		Dens,
		R,
		G,
		B
	};

class InctImage{
private:
	int iwidth;
	int iheight;
	int idepth;
	int cmode;
	string magicN;
	string iFilename;
	int channel;
	static void showImageInfo(InctImage &Image);
public:
	vector<unsigned char> dat; //自家で弄りたい時もあろうかと・・・
	InctImage();
	InctImage(int width,int height,int depth, string mn);
	InctImage(int width,int height,int depth, int cmode);
	InctImage(const InctImage &obj);
	~InctImage();
	void loadppmimage(string filename);
	void setPnmPixel(int x,int y, RGBColor _rgb);
	RGBColor getPnmPixel(int x,int y) const;
	InctImage &clonePnmImage();
	static InctImage &clonePnmImage(InctImage &source);
	//{
	//		InctImage *temp = new InctImage(source.getWidth(),source.getHeight(),source.getDepth(),source.getMagicNumber());
	//		InctImage &tmp = *temp;
	//		return tmp;
	//}
	static void savePnmImage(InctImage &source,string filename);
	void setFileName(string filename);
	void savePnmImage(string filename);
	void savePnmImage();
	int getWidth() const{return iwidth;};
	int getHeight() const{return iheight;};
	int getDepth() const{return idepth;};
	int getImageMode() const{return cmode;};
	string getMagicNumber() const{return magicN;};
	void ReleaseImage();	
};



class Iimc{
public:
	Iimc();
	~Iimc();
	void Initialize();
	void DestructImageList();
	void LoadImageFile(string filename,string nickname);
	//画像情報取得用関数
	InctImage* GetImagePointer(string nickname);
	int GetImageWidth(string nickname);
	int GetImageHeight(string nickname);
	int GetImageDepth(string nickname);
	int GetImageMode(string nickname);
	string GetImageMagicNumber(string nickname);
	RGBColor GetPixelVal(string nickname,int x,int y);

	void SetPixelVal(string nickname,int x,int y,enum RGB, unsigned char pixelval);
	void SetPixelRGB(string nickname,int x,int y,unsigned char _R,unsigned char _G,unsigned char _B);
	void SetPixelVal(string nickname,int x,int y,RGBColor tRGB);

	void SaveImageFile(string savename);
	void SaveImageFile(string source, string savename);
	void DestructImageLib(void);
	void CopyImageVal(string source,string dist);
	InctImage& getImage(string nickname);

	void CreateImage(int _width,int _height,int _depth, int _cmode, string nickname);
	void CloneImage(string simagename,string dimagename);
	void deleteImage(string nickname);

private:
	int getImageIndex(string nickname);
	int imageNumber;
	vector<InctImage *> gImageList;
	map<string,int> gImageNames;
	void setImageIndex(string nickname,InctImage *image);
};

////===========================================================================================================
//void InitImageLib(void);
//void CreateImage(int _width,int _height,int _cmode,char *imagename);
//void CloneImage(char *simagename,char *clnimagename);
//void LoadImageFile(char *imagefilename,char *imagename);
//unsigned char GetPixelVal(char *simagename,int x,int y,int color);
//void SetPixelVal(char *simagename,int x,int y,int color,unsigned char pixelval);
//void SetPixelRGB(char *simagename,int x,int y,unsigned char _R,unsigned char _G,unsigned char _B);
//void SetPixelVal(char *simagename,int x,int y,struct RGBColor tRGB);
//void SaveImageFile(char *simagename);
//void SaveImageFile(char *simagename,char *savefilename);
//void DestructImageLib(void);
//void CopyImageVal(char *simagename,char *dimagename);
////画像情報取得用関数
//struct ppmimg* GetImagePointer(char *simagename);
//int GetImageWidth(char *simagename);
//int GetImageHeight(char *simagename);
//int GetImageDepth(char *simagename);
//int GetImageMode(char *simagename);
//char* GetImageMagicNumber(char *simagename);
//struct RGBColor GetPixelVal(char *simagename,int x,int y);

//
//
////グローバル領域の関数たち
//
//int getImageIndex(char *imagename);
//void setImageIndex(char *imagename,struct ppmimg *simg);
