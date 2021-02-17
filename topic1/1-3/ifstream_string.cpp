#pragma once

#include "ifstream_string.h"

struct PnmHeader header;

using namespace std;


std::ostream& operator<<(std::ostream& os, const RGBColor& _col)
{
	return ( os << "RGB_DENS(" <<  (int)_col.getR()  << ',' <<  (int)_col.getG() << ',' << (int)_col.getB() << ")_(" << (int)_col.getDens()) << ')';
	//return ( os << "RGB_DENS(" <<  _col.getR()  << ',' <<  _col.getG() << ',' << _col.getB() << ")_(" << _col.getDens()) << ')';
}

InctImage::InctImage()
{
	iwidth=0;
	iheight=0;
	idepth=0;
	cmode=-1;
	dat.clear();
	magicN = "";
	iFilename = "";
	channel = 0;
}


//�R�s�[�R���X�g���N�^
InctImage::InctImage(const InctImage &obj)
{
	iwidth=obj.iwidth;
	iheight=obj.iheight;
	idepth=obj.idepth;
	cmode=obj.cmode;
	channel = obj.channel;
	int size = obj.getWidth()*obj.getHeight()*channel;
	dat.assign(size,0);
	/*vector<unsigned char>::const_iterator theI;
	for(theI = obj.dat.begin();theI!=obj.dat.end();theI++){
	dat.push_back(*theI);
	}*/
	//dat = obj.dat;
	magicN = obj.magicN;
	iFilename = "";
	channel = obj.channel;
}



void InctImage::setFileName(string filename){
	this->iFilename = filename;
}

InctImage::InctImage(int width,int height,int depth, string mn)
{
	//int channel = 0;
	iwidth=width;
	iheight=height;
	idepth=depth;
	magicN = mn;
	iFilename = "";


	if(mn=="P1"){
		cmode=0;
		channel = 1;
	}else if(mn=="P2"){
		cmode=1;
		channel = 1;
	}else if(mn=="P3"){
		cmode=2;
		channel = 3;
	}else if(mn=="P4"){
		cmode=3;
		channel = 1;
	}else if(mn=="P5"){
		cmode=4;
		channel = 1;
	}else if(mn=="P6"){
		cmode=5;
		channel = 3;
	}
	int size = iwidth * iheight*channel;

	dat.assign(size, 0);
}

void InctImage::setInFileName(string inFileName){
	inFile = inFileName;
}


InctImage::InctImage(int width,int height,int depth, int cmode)
{
		//int channel = 0;
	iwidth=width;
	iheight=height;
	idepth=depth;
	//magicN = mn;
	iFilename = "";
    this->cmode = cmode;  

	switch(cmode)
	{
	case 0:magicN="P1";channel = 1;break;
	case 1:magicN="P2";channel = 1;break;
	case 2:magicN="P3";channel = 3;break;
	case 3:magicN="P4";channel = 1;break;
	case 4:magicN="P5";channel = 1;break;
	case 5:magicN="P6";channel = 3;break;
	}

	int size = iwidth * iheight * channel;

	dat.assign(size, 0);

}
void InctImage::setPnmPixel(int x,int y, RGBColor _rgb)
{
	if(this->cmode == 0 || this->cmode == 3){
		dat[iwidth*y+x] = _rgb.Bit;
	}else if(this->cmode == 1 || this->cmode == 4){
		dat[iwidth*y+x] = _rgb.Dens;
	}else if(this->cmode == 2 || this->cmode == 5){
		dat[3*(iwidth*y+x)] =_rgb.R;
		dat[3*(iwidth*y+x)+1] =_rgb.G;
		dat[3*(iwidth*y+x)+2] =_rgb.B;
	}else{
		cout << "file mode have not setted" << endl;
		exit(1);
	}

}

InctImage &InctImage::clonePnmImage()
{
	InctImage *temp = new InctImage(this->iwidth,this->iheight,this->idepth,this->magicN);
	InctImage &tmp = *temp;
	return tmp;
}

InctImage& InctImage::clonePnmImage(InctImage &source)
{
	InctImage *temp = new InctImage(source.getWidth(),source.getHeight(),source.getDepth(),source.getMagicNumber());
	InctImage &tmp = *temp;
	return tmp;
}


RGBColor InctImage::getPnmPixel(int x,int y) const
{
	RGBColor _rgb;
	if(this->cmode == 0 || this->cmode == 3){
		_rgb.Bit = dat[iwidth*y+x];
		return(_rgb);
	}
	else if(this->cmode == 1 || this->cmode == 4){
		_rgb.Dens = dat[iwidth*y+x];
		return(_rgb);
	}
	else if(this->cmode == 2 || this->cmode == 5){
//		cout << dat.size() << endl;
		_rgb.setRGB(dat[3*(iwidth*y+x)],dat[3*(iwidth*y+x)+1],dat[3*(iwidth*y+x)+2]);
		return(_rgb);
	}
	else{
		cout << "file mode have not setted in getPnmPixel" << endl;
		exit(1);
	}

}

void InctImage::savePnmImage(InctImage &source, string filename)
{
	ofstream outfile;

	switch(source.cmode){
	case 0:
	case 1:
	case 2:outfile.open(filename,std::ios::out);break;
	case 3:
	case 4:
	case 5:outfile.open(filename,std::ios::out|std::ios::binary);break;
	default:cout << "mode error exiting program." << endl;exit(0);break;
	}
	cout << "Now Saving Image File" << endl;
	cout << "..." << endl;
	outfile << source.magicN << endl;
	outfile << source.iwidth << " " << source.iheight << endl;
	if(source.cmode != 0 && source.cmode != 3){
		outfile << source.idepth << endl;
	}

	cout << "...Image Infomation is valid" << endl;
	if(source.cmode < 3){
		vector<unsigned char>::iterator theI;
		int n=0;
		theI=source.dat.begin();
		for(int j=0;j<source.iheight;j++){
			for(int i=0;i<source.iwidth;i++){
				if(source.cmode == 2){
					outfile << (int)(*theI) <<" " << (int)(*(theI+1)) << " " << (int)(*(theI+2));
					if( i != source.iwidth-1)outfile << " ";
					theI+=3;
				}else{
					outfile << (int)(*theI);
					if( i != source.iwidth-1)outfile << " ";
					theI++;
				}
			}
			outfile << endl;
		}
		cout << "..." << endl;
	}else{
		vector<unsigned char>::iterator theI;
		theI = source.dat.begin();
		if(source.cmode == 5){
			outfile.write(reinterpret_cast<char *>(&(*theI)),source.iwidth*source.iheight*3);
			cout << "..." << endl;
		}else if(source.cmode == 4){
			outfile.write(reinterpret_cast<char *>(&(*theI)),source.iwidth*source.iheight);
			cout << "..." << endl;
		}else{
			vector<char> bitstr;
			int bitsize = source.iwidth * source.iheight;
			int _maxroop = bitsize - bitsize%8;
			int _lastroop = bitsize%8;
			bitset<8> _bit;
			int k=0;
			int n=0;
			while(k<_maxroop){
				if(source.dat[k] == 1){
					_bit.set(n);
				}else{
					_bit.reset(n);
				}
				//_bit[n] = source.dat[k];
				if(n==7){
					unsigned char _str = (unsigned char)_bit.to_ulong();
					bitstr.push_back(_str);
					n=0;
				}else n++;
				k++;
			}
			_bit = 0x0;
			for(int i=_maxroop;i<bitsize;i++){

				if(source.dat[i] == 1){
					_bit.set((i-_maxroop));
				}else{
					_bit.reset((i-_maxroop));
				}
			}
			if(_maxroop != bitsize){
				bitstr.push_back((unsigned char)_bit.to_ulong());
			}
			//cout << "str size is " <<  bitstr.size() << endl;
			cout << "..." << endl;
			vector<char>::iterator theII;
			for(theII=bitstr.begin();theII!=bitstr.end();theII++){
				outfile.write(reinterpret_cast<char *>(&(*theII)),sizeof(unsigned char));
			}
		}
	}
	source.setFileName(filename);
	cout << "...File Closing OK" << endl;
	if(outfile.is_open())outfile.close();
	cout << "Now Saving Process Successfully Completed!" << endl << endl;;
	cout << "Saved Image Infomation " << endl;
	showImageInfo(source);
}


void InctImage::savePnmImage(string filename)
{
	ofstream outfile;

	switch(this->cmode){
	case 0:
	case 1:
	case 2:outfile.open(filename,std::ios::out);break;
	case 3:
	case 4:
	case 5:outfile.open(filename,std::ios::out|std::ios::binary);break;
	default:cout << "mode error exiting program." << endl;exit(0);break;
	}
	cout << "Now Saving Image File" << endl;
	cout << "..." << endl;
	outfile << this->magicN << endl;
	outfile << this->iwidth << " " << this->iheight << endl;
	if(this->cmode != 0 && this->cmode != 3){
		outfile << this->idepth << endl;
	}

	cout << "...Image Infomation is valid" << endl;
	if(this->cmode < 3){
		vector<unsigned char>::iterator theI;
		int n=0;
		theI=this->dat.begin();
		for(int j=0;j<this->iheight;j++){
			for(int i=0;i<this->iwidth;i++){
				if(this->cmode == 2){
					outfile << (int)(*theI) <<" " << (int)(*(theI+1)) << " " << (int)(*(theI+2));
					if( i != this->iwidth-1)outfile << " ";
					theI+=3;
				}else{
					outfile << (int)(*theI);
					if( i != this->iwidth-1)outfile << " ";
					theI++;
				}
			}
			outfile << endl;
		}
		cout << "..." << endl;
	}else{
		vector<unsigned char>::iterator theI;
		theI = this->dat.begin();
		if(this->cmode == 5){
			outfile.write(reinterpret_cast<char *>(&(*theI)),this->iwidth*this->iheight*3);
			cout << "..." << endl;
		}else if(this->cmode == 4){
			outfile.write(reinterpret_cast<char *>(&(*theI)),this->iwidth*this->iheight);
			cout << "..." << endl;
		}else{
			vector<char> bitstr;
			int bitsize = this->iwidth * this->iheight;
			int _maxroop = bitsize - bitsize%8;
			int _lastroop = bitsize%8;
			bitset<8> _bit;
			int k=0;
			int n=0;
			while(k<_maxroop){
				if(this->dat[k] == 1){
					_bit.set(n);
				}else{
					_bit.reset(n);
				}
				//_bit[n] = this->dat[k];
				if(n==7){
					unsigned char _str = (unsigned char)_bit.to_ulong();
					bitstr.push_back(_str);
					n=0;
				}else n++;
				k++;
			}
			_bit = 0x0;
			for(int i=_maxroop;i<bitsize;i++){

				if(this->dat[i] == 1){
					_bit.set((i-_maxroop));
				}else{
					_bit.reset((i-_maxroop));
				}
			}
			if(_maxroop != bitsize){
				bitstr.push_back((unsigned char)_bit.to_ulong());
			}
			//cout << "str size is " <<  bitstr.size() << endl;
			cout << "..." << endl;
			vector<char>::iterator theII;
			for(theII=bitstr.begin();theII!=bitstr.end();theII++){
				outfile.write(reinterpret_cast<char *>(&(*theII)),sizeof(unsigned char));
			}
		}
	}
	this->setFileName(filename);
	cout << "...File Closing OK" << endl;
	if(outfile.is_open())outfile.close();
	cout << "Now Saving Process Successfully Completed!" << endl << endl;;
	cout << "Saved Image Infomation " << endl;
	showImageInfo(*this);
}

void InctImage::savePnmImage()
{
	ofstream outfile;

	if(this->iFilename != ""){

		switch(this->cmode){
		case 0:
		case 1:
		case 2:outfile.open(this->iFilename,std::ios::out);break;
		case 3:
		case 4:
		case 5:outfile.open(this->iFilename,std::ios::out|std::ios::binary);break;
		default:cout << "mode error exiting program." << endl;exit(0);break;
		}
		if(this->dat.size() == 0){
			cout << "Image data is incomplete" << endl;
			exit(1);
		}
		cout << "Now Saving Image File" << endl;
		cout << "..." << endl;
		outfile << this->magicN << endl;
		outfile << this->iwidth << " " << this->iheight << endl;
		if(this->cmode != 0 && this->cmode != 3){
			outfile << this->idepth << endl;
		}

		cout << "...Image Infomation is valid" << endl;
		if(this->cmode < 3){
			vector<unsigned char>::iterator theI;
			int n=0;
			theI=this->dat.begin();
			for(int j=0;j<this->iheight;j++){
				for(int i=0;i<this->iwidth;i++){
					if(this->cmode == 2){
						outfile << (int)(*theI) <<" " << (int)(*(theI+1)) << " " << (int)(*(theI+2));
						if( i != this->iwidth-1)outfile << " ";
						theI+=3;
					}else{
						outfile << (int)(*theI);
						if( i != this->iwidth-1)outfile << " ";
						theI++;
					}
				}
				outfile << endl;
			}
			cout << "..." << endl;
		}else{
			vector<unsigned char>::iterator theI;
			theI = this->dat.begin();
			if(this->cmode == 5){
				outfile.write(reinterpret_cast<char *>(&(*theI)),this->iwidth*this->iheight*3);
				cout << "..." << endl;
			}else if(this->cmode == 4){
				outfile.write(reinterpret_cast<char *>(&(*theI)),this->iwidth*this->iheight);
				cout << "..." << endl;
			}else{
				vector<char> bitstr;
				int bitsize = this->iwidth * this->iheight;
				int _maxroop = bitsize - bitsize%8;
				int _lastroop = bitsize%8;
				bitset<8> _bit;
				int k=0;
				int n=0;
				while(k<_maxroop){
					if(this->dat[k] == 1){
						_bit.set(n);
					}else{
						_bit.reset(n);
					}
					//_bit[n] = this->dat[k];
					if(n==7){
						unsigned char _str = (unsigned char)_bit.to_ulong();
						bitstr.push_back(_str);
						n=0;
					}else n++;
					k++;
				}
				_bit = 0x0;
				for(int i=_maxroop;i<bitsize;i++){

					if(this->dat[i] == 1){
						_bit.set((i-_maxroop));
					}else{
						_bit.reset((i-_maxroop));
					}
				}
				if(_maxroop != bitsize){
					bitstr.push_back((unsigned char)_bit.to_ulong());
				}
				//cout << "str size is " <<  bitstr.size() << endl;
				cout << "..." << endl;
				vector<char>::iterator theII;
				for(theII=bitstr.begin();theII!=bitstr.end();theII++){
					outfile.write(reinterpret_cast<char *>(&(*theII)),sizeof(unsigned char));
				}
			}
		}
		cout << "...File Closing OK" << endl;
		if(outfile.is_open())outfile.close();
		cout << "Now Saving Process Successfully Completed!" << endl << endl;;
		cout << "Saved Image Infomation " << endl;

		showImageInfo(*this);
	}else{
		cout << "ImageFileName has not been set!\n You must set filename before Use this Function, or Use Other Instances" << endl;
		exit(1);
	}
}


InctImage::~InctImage()
{
	if(!dat.empty()){
		dat.erase(dat.begin(),dat.end());
		dat.clear();
	}
}

void InctImage::loadppmimage(string filename)
{
	istringstream hstream;
	std::vector<string> head_list;
	string st,head_str;
	ifstream infile;

	setInFileName(filename);

	cout << "Image Open Process Start!" << endl;
	cout << "Input File Name is " << filename << endl;
	infile.open(filename.c_str(),ios::binary);
	if(infile.fail()){
		cerr << "Error File not Found" << endl;
		cerr << "Exiting Program" << endl;
		exit(1);
	}

	string tmp2 = "P3";
	getline(infile,head_str);
	int tmp = 0;
	if(head_str[0] == 'P')
	{
		if(head_str[head_str.size()-1] == '\r'){
			cout << "this file include \'CR\'" << endl;
			throw "this file include \'CR\'";
		}
		header.Pnum.assign(head_str);
		magicN = head_str;
		cout << "Magig Number is " << head_str << endl;
		if(head_str=="P1"){
			cmode=0;
			channel = 1;
		}else if(head_str=="P2"){
			cmode=1;
			channel = 1;
		}else if(head_str=="P3"){
			cmode=2;
			channel = 3;
		}else if(head_str=="P4")
		{
			cmode=3;
			channel = 1;
		}else if(head_str=="P5"){
			cmode=4;
			channel = 1;
		}else if(head_str=="P6"){
			cmode=5;
			channel = 3;
		}


	}else{
		cout << "This File is not P'N'M Image Format" << endl;
	}

	getline(infile,head_str);
	if(head_str[0] == '#'){
		getline(infile,head_str);
	}
	hstream.str(head_str);
	hstream >> header.Width >> header.Height;
	hstream.clear();
	hstream.str(head_str);
	hstream >> iwidth >> iheight;
	//cout << iwidth << "," << iheight << endl;

	if(!(header.Pnum == "P1" || header.Pnum == "P4"))
	{
		getline(infile,head_str);
//		cout << "Depth : " << head_str << endl;
		this->idepth = stoi(head_str);
	}else{
		cout << "This Image is PBM(Ascii or Binary)" << endl;
	}

	if(header.Pnum == "P4" || header.Pnum == "P5")
	{
		ios::pos_type pstart = infile.tellg();
		ios::pos_type pend = infile.seekg(0,ios_base::end).tellg();
		dat.resize((unsigned int)(pend-pstart));
		infile.clear();
		infile.seekg(pstart,ios::beg);
		infile.read((char *)(&(dat[0])),pend-pstart);
		if(header.Pnum == "P4"){
			vector<unsigned char> _dat;
			_dat.assign(this->iwidth*this->iheight,(unsigned char)0);
			int k=0,n=0;
			for(int i=0;i< ( pend - pstart);i++){
				for(int j=0;j<8;j++){
					_dat[n] = this->dat[i] &  1;
					this->dat[i] >>= 1;
					n++;
				}
			}
			dat.resize(this->iwidth*this->iheight);
			dat = _dat;
		}
	}else if(header.Pnum == "P6"){
		ios::pos_type pstart = infile.tellg();
		ios::pos_type pend = infile.seekg(0,ios_base::end).tellg();
		dat.resize((unsigned int)(pend-pstart));
		infile.clear();
		infile.seekg(pstart,ios::beg);
		infile.read((char *)(&(dat[0])),pend-pstart);
	}else if(header.Pnum == "P1" || header.Pnum == "P2" || header.Pnum == "P3"){
		int k=0;
		int ppp;
		switch(cmode){
		case 0:dat.assign(iwidth*iheight,0);break;
		case 1:dat.assign(iwidth*iheight,0);break;
		case 2:dat.assign(iwidth*iheight*3,0);break;
		default:break;
		}
		string temp;
		while(getline(infile,temp)){
			stringstream is(temp);
			while(is >> ppp){
				dat[k] = ppp;
				k++;
			}
		}

		//cout << "dat.size() = " << dat.size() << endl;
		cout << "total data size is " << k-1 << " byte" << endl;
	}
	else{
		cout << "ssdfjas;ldgj" << endl;
	}

	cout << "Open Process Successfully Completed!" << endl;
	showImageInfo(*this);

}

void InctImage::ReleaseImage()
{
	this->dat.erase(dat.begin(),dat.end());
}

void InctImage::showImageInfo(InctImage &Image)
{
	cout << endl;
	cout << "--------  Image Infomation  --------" << endl;
	cout << "Image File Name : " << Image.iFilename << endl;
	cout << "   Magic Number : " << Image.magicN << endl;
	cout << "  Size Of Image : (" <<Image.iwidth << "," << Image.iheight << ")" << endl;
	if(Image.magicN == "P1" || Image.magicN == "P4")cout <<  " Depth Of Image : " << "--" << endl;
	cout << " Depth Of Image : " << Image.idepth << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
}

/*
P1	2�l ascii�`��	PBM�`��
P2	�O���[�X�P�[�� ascii�`��	PGM�`��
P3	�t���J���[ ascii�`��	PPM�`��
P4	2�l raw�`��	PBM�`��
P5	�O���[�X�P�[�� raw�`��	PGM�`��
P6	�t���J���[ raw�`��	PPM�`��
*/

Iimc::Iimc()
{
	imageNumber=0;
	Initialize();
}

void Iimc::Initialize(){
	gImageList.clear();
	gImageNames.clear();
	imageNumber = 0;
}

void Iimc::DestructImageList(){
	vector<InctImage *>::iterator theI;
	for(theI=gImageList.begin();theI!=gImageList.end();theI++){
		if(!(*theI)->dat.empty()){
			(*theI)->dat.erase((*theI)->dat.begin(),(*theI)->dat.end());
		}

	}

	imageNumber = 0;
}


Iimc::~Iimc()
{
	cout << "destructing" <<endl;
}


void Iimc::LoadImageFile(string filename, string nickname){	//���O�̏d���������Ȃ��Ƃ���
	//struct ppmimg *ppmtmp;//=NULL;//
	if(getImageIndex(nickname) > 0){
		cout << "This nickname is already used." << endl;
		exit(1);
	}
	InctImage *temp = new InctImage;
	temp->loadppmimage(filename);
	cout << "LoadImageFile(" << filename << ")as " << nickname << endl;
	setImageIndex(nickname,temp);
}

void Iimc::CreateImage(int _width,int _height,int _depth,int _cmode, string nickname)
{
	if(getImageIndex(nickname) > 0){
		cout << "This nickname is already used." << endl;
		exit(1);
	}
	InctImage *ppmtmp=new InctImage(_width,_height,_depth,_cmode);
	setImageIndex(nickname,ppmtmp);
}
void Iimc::CloneImage(string simagename, string dimagename)
{
	InctImage *ppmtmp,*cloneimg=NULL;
	
	cout << "Create and Copy ImageValue " << simagename << " to " << dimagename << endl;
	
	int idx = getImageIndex(simagename);
	if(idx != -1){
		ppmtmp = gImageList[idx];
	}else{
		cout << simagename << "�Ƃ������O�̉摜�͂���܂���" << endl;
		exit(1);
	}
	cloneimg = new InctImage(ppmtmp->getWidth(),ppmtmp->getHeight(),ppmtmp->getDepth(),ppmtmp->getImageMode());

	InctImage & cimg = *cloneimg;
	InctImage & simg = *ppmtmp;
	cimg = InctImage::clonePnmImage(simg);
	//cimg = simg.clonePnmImage();
	setImageIndex(dimagename,cloneimg);
	CopyImageVal(simagename,dimagename);
}

void Iimc::setImageIndex(string nickname,InctImage *image){
	gImageList.push_back(image);
	gImageNames.insert(pair<string, int>(nickname,imageNumber));
	imageNumber++;
}

//�摜���擾�p�֐�
InctImage* Iimc::GetImagePointer(string nickname){
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp);
}
int Iimc::GetImageWidth(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp->getWidth());
}
int Iimc::GetImageHeight(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp->getHeight());
}
int Iimc::GetImageDepth(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp->getDepth());
}

int Iimc::GetImageMode(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp->getImageMode());
}

string Iimc::GetImageMagicNumber(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	return(ppmtmp->getMagicNumber());
}
RGBColor Iimc::GetPixelVal(string nickname,int x,int y)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	RGBColor tRGB;
	tRGB=ppmtmp->getPnmPixel(x,y);
	return(tRGB);
}

int Iimc::getImageIndex(string nickname)
{
	map<string,int>::iterator itr;
	itr = gImageNames.find(string(nickname));
	if(itr == gImageNames.end()){
		//printf("%s�Ƃ������O�̉摜�͂���܂���",nickname);
		//cout << nickname << " �Ƃ������O�̉摜�͂���܂���" << endl;
		return -1;
	}else{
		return(itr->second); 
	}
}

void Iimc::SetPixelVal(string nickname,int x,int y, enum RGB _rgb, unsigned char pixelval)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	RGBColor scolor;
	if(ppmtmp->getImageMode() == 1){
		scolor.Dens = pixelval;
	}else if(_rgb == Dens && ppmtmp->getImageMode() == 3){
		printf("�J���[���[�h���s���ł��D\n");
		exit(1);
	}else{
		scolor = ppmtmp->getPnmPixel(x,y);
		switch(_rgb){
		case R:scolor.R = pixelval;break;
		case G:scolor.G = pixelval;break;
		case B:scolor.B = pixelval;break;
		default:scolor.R = 0;scolor.G = 0;scolor.B = 0;break;
		}	
	}
	ppmtmp->setPnmPixel(x,y,scolor);
}


void Iimc::SetPixelRGB(string nickname,int x, int y, unsigned char _R, unsigned char _G, unsigned char _B)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	class RGBColor scolor;
	if(ppmtmp->getImageMode() == 1){
		printf("�J���[���[�h�̈Ⴄ�摜�ł��D\n");
		exit(1);
	}else{
		scolor.R = _R;
		scolor.G = _G;
		scolor.B = _B;
		ppmtmp->setPnmPixel(x,y,scolor);
	}
}


void Iimc::SetPixelVal(string nickname,int x, int y, RGBColor tRGB)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	ppmtmp->setPnmPixel(x,y,tRGB);
}

void  Iimc::SaveImageFile(string savename)
{
	int idx = getImageIndex(savename);
	InctImage* ppmtmp = gImageList[idx];
	std::string sname(savename);
	std::string fname;
	if(ppmtmp->getImageMode() == 1){
		std::string suffix(".pgm");
		fname = sname + suffix;
	}else{
		std::string suffix(".ppm");
		fname = sname + suffix;		
	}
	ppmtmp->savePnmImage(fname);
}

InctImage& Iimc::getImage(string nickname)
{
	int idx = getImageIndex(nickname);
	InctImage* ppmtmp = gImageList[idx];
	InctImage& tmp = *ppmtmp;
	return tmp;
}

void Iimc::deleteImage(string nickname)
{
	map<string,int>::iterator itr;
	itr = gImageNames.find(string(nickname));
	if(itr == gImageNames.end()){
		//printf("%s�Ƃ������O�̉摜�͂���܂���",nickname);
		cout << nickname << " �Ƃ������O�̉摜�͂���܂���" << endl;
		cout << "�������܂���" << endl;
	}else{
		gImageNames.erase(itr);
	}
}

void  Iimc::SaveImageFile(string source, string savename)
{
	int idx = getImageIndex(source);
	InctImage* ppmtmp = gImageList[idx];

	ppmtmp->savePnmImage(savename);
}
void  Iimc::DestructImageLib()
{
	vector<InctImage *>::iterator theI;
	for(theI=gImageList.begin();theI!=gImageList.end();theI++){
		//deleteppmimg(*theI);
		if( *theI != NULL){
			delete *theI;
		}

	}
	if(!gImageList.empty()){
		gImageList.erase(gImageList.begin(),gImageList.end());
		gImageList.clear();
		gImageNames.clear();
	}
	imageNumber = 0;
}
void  Iimc::CopyImageVal(string source,string nickname)
{
	cout << "CopyImageVal(source : " << source << ",dist : " << nickname << ")" << endl;
	//printf("CopyImageVal(source:%s,dist:%s)\n",simagename,dimagename);
	//string a(source),b(dimagename);

	//printf("CopyImageVal(source:%s,dist:%s)\n",a.c_str(),b.c_str());
	InctImage *sim,*dim;

	int idx1 = getImageIndex(source);
	int idx2 = getImageIndex(nickname);

	if(idx1 != -1){
		sim = gImageList[idx1];
	}else{
		cout << "Source : " <<  source << " �Ƃ������O�̉摜�͂���܂���" << endl;
		//printf("Source:%s�Ƃ������O�̉摜�͂���܂���\n",simagename);
		exit(1);
	}
	if(idx2 != -1){
		dim = gImageList[idx2];
	}else{
		cout << "Dist : " <<  nickname << " �Ƃ������O�̉摜�͂���܂���" << endl;
		//printf("Dist:%s�Ƃ������O�̉摜�͂���܂���",dimagename);
		exit(1);
	}
	//if(sim->dat.size() != dim->dat.size()){
	//	cout <<  "Image size does not match" << endl;
	//}
	long datasize = sim->dat.size();
	//long datsize = sim->iheight*sim->iwidth*sim->cmode;
	dim->dat.assign(sim->dat.begin(),sim->dat.end());
	//std::copy(sim->dat.begin(),sim->dat.end(),dim->dat.begin());
	//memcpy(dim->dat,sim->dat,datsize);
}