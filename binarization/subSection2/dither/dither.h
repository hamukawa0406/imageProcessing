
class dither {
    private:
		int channel;
		int threshold;
	    static const int bayer[4][4];
	    static const int halftone[4][4];
	    static const int screw[4][4];
	    static const int screw2[4][4];
	    static const int medEmph[4][4];
	    static const int dotConc[4][4];
		int dthr[4][4];
	public:
		dither();
		dither(int);
		int getDither(int i, int j);
		void dithering(struct ppmimg *src, struct ppmimg *dst, int i, int j);
		int calcDither(int x, int y);
		bool judgeBinarization(unsigned char dens);


};