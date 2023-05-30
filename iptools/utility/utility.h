#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <sstream>
#include <math.h>

class utility
{
 // private:
  
	public:
		utility();
    //utility(int colnum,int rownum);
    void resize (int numberOfRows, int numberOfColumns);  
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value); 
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
    static void dualthres(image &src, image&tgt,int T, int V1, int V2); 
    static void reg2dsmooth(image &src,image &tgt, int ws); //blurring
    static void colorvisual(image &src, image &tgt, int T, int V1); 
    static void colorbright(image &src, image &tgt, int DR, int DG, int DB);

    static void roi(image &src, image &tgt, int x, int y, int sx, int sy, int flag); 
    static void histoMake(image &tgt); //used to check histogram of image
    static void combineMod(image &src, image &tgt, image &m1, int* first, int flag); 
  
    static void histostretch(image &src,image &tgt, int A, int B);  
    static void histostretchnorm(image &src, image &tgt); 
    static void histothres(image &src,image &tgt, int T, char *G, int A, int B); 
    static void colorstretch(image &src, image &tgt, char* C, int A, int B); 
    static void rgbtohsi(image &src,image &tgt); 
    static void hsistretch(image &src,image &tgt, int A, int B); //use hsi image as input
    static void hsistretchnorm(image &src,image &tgt); 
    static void hsitorgb(image &src, image &tgt);
    static void sobel3(image &src, image &tgt); 
    static void sobel5(image &src, image &tgt);
    static void binaryedge(image &src, image &tgt, int TH, int TL); 


};

#endif

