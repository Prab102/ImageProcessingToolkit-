#include "utility.h"
#include <strings.h>
#include <string.h>
#include "math.h"
#define MAXRGB 255
#define MINRGB 0
#define MAXLEN 256
using namespace std;
std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}


int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	
   
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)                         
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		} 
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

void utility::reg2dsmooth(image &src, image &tgt,int ws)
{
  double Sum = 0;
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  //window size 3
  if(ws == 3){
    //keeps edges in bounds
    for (int i=1; i<src.getNumberOfRows()-1; i++)  
    {
      for (int j=1; j<src.getNumberOfColumns()-1; j++)
      {
        Sum += src.getPixel(i-1,j+1); 
        Sum += src.getPixel(i+0,j+1); 
        Sum += src.getPixel(i+1,j+1); 
        Sum += src.getPixel(i-1,j+0); 
        Sum += src.getPixel(i+0,j+0); 
        Sum += src.getPixel(i+1,j+0); 
        Sum += src.getPixel(i-1,j-1); 
        Sum += src.getPixel(i+0,j-1); 
        Sum += src.getPixel(i+1,j-1);

        Sum = Sum /9;

        tgt.setPixel(i,j,Sum); 
          
      }
    }
  }
  //window size 5
  if(ws == 5){
    //keeps edges in bounds
    for (int i=2; i<src.getNumberOfRows()-2; i++)  
    {
      for (int j=2; j<src.getNumberOfColumns()-2; j++)
      {
        Sum += src.getPixel(i-2,j+2); 
        Sum += src.getPixel(i-1,j+2); 
        Sum += src.getPixel(i+0,j+2); 
        Sum += src.getPixel(i+1,j+2); 
        Sum += src.getPixel(i+2,j+2); 
        Sum += src.getPixel(i-2,j+1); 
        Sum += src.getPixel(i-1,j+1); 
        Sum += src.getPixel(i+0,j+1); 
        Sum += src.getPixel(i+1,j+1); 
        Sum += src.getPixel(i+2,j+1); 
        Sum += src.getPixel(i-2,j+0); 
        Sum += src.getPixel(i-1,j+0); 
        Sum += src.getPixel(i+0,j+0); 
        Sum += src.getPixel(i+1,j+0); 
        Sum += src.getPixel(i+2,j+0); 
        Sum += src.getPixel(i-2,j-1); 
        Sum += src.getPixel(i-1,j-1); 
        Sum += src.getPixel(i+0,j-1); 
        Sum += src.getPixel(i+1,j-1); 
        Sum += src.getPixel(i+2,j-1); 
        Sum += src.getPixel(i-2,j-2); 
        Sum += src.getPixel(i-1,j-2); 
        Sum += src.getPixel(i+0,j-2); 
        Sum += src.getPixel(i+1,j-2); 
        Sum += src.getPixel(i+2,j-2); 

        Sum = Sum /25;

        tgt.setPixel(i,j,Sum); 
          
      }
    }
  }

}

/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
void utility::colorvisual(image &src, image &tgt, int T, int V1)
{
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
      int pixelSize = src.getPixel(i,j);
       
			if ( abs(V1 - src.getPixel(i,j)) < T)
      {
       
        tgt.setPixel(i,j,RED,pixelSize);
        
      }  
			else{
       	
         tgt.setPixel(i,j,RED,pixelSize);
         tgt.setPixel(i,j,BLUE,pixelSize);
         tgt.setPixel(i,j,GREEN,pixelSize);
      }
		}
	}

}

/*------------------------------------------------------------------------*/
void utility::histostretch(image &src, image &tgt, int A, int B)
{
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  image histogram;
  utility::histoMake(src);
  float histoarr[256] = {0};
      //creates array representing histogram
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
              histoarr[src.getPixel(i,j)] = histoarr[src.getPixel(i,j)] + 1;     
              
         }   
      }
 
  
   float Imin = 0;
   float Imax = 0;
   int pos = 0;
   //getting min position in histogram
   for(int i = 0; i<256; i++)             
   {
      if(histoarr[i] == 0)
      {
        pos++;
      }
      else
        break;
   }
   
  
   Imin = pos;  //C
   
   pos = 255;
   //getting max position in hist
   for(int i = 255; i>0; i--)           
    {
     if(histoarr[i] == 0)
     {
         
         pos--;
     }
     else
       break;
    }
   
    Imax = pos;       //D
    
    
    float P;
    
    for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
             //histogram stretching equation applied
             P = (src.getPixel(i,j) - Imin)*((B-A)/(Imax-Imin)) + A; 
             tgt.setPixel(i,j,P);
         }   
      }



}
//histostretchnormalization
/*------------------------------------------------------------------------*/
void utility::histostretchnorm(image &src, image &tgt)
{
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  float histoarr[50000] = {0};
   int count =0;
      //gets histogram of image
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
              histoarr[src.getPixel(i,j)] = histoarr[src.getPixel(i,j)] + 1;      
             
         }   
      }
 
  
   float Imin = 0;
   float Imax = 0;
   int pos = 0;
   for(int i = 0; i<50000; i++)             
   {
     if(histoarr[i] == 0)
     {
      pos++;
     }
     else
       break;
   }
   
  
   Imin = pos;  //C
   
   pos = 49000;
    for(int i = 49000; i>0; i--)           
   {
     if(histoarr[i] == 0)
     {
      pos--;
     }
     else
       break;
   }
    Imax = pos;       //D
    
    
    float P;
    
    for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
             P = (src.getPixel(i,j) - Imin)*((255-0)/(Imax-Imin)) + 0;      
             tgt.setPixel(i,j,P);
         }   
      }

}

/*------------------------------------------------------------------------*/
void utility::histothres(image &src, image &tgt, int T, char* G, int A, int B)
{
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  float histoarr[256] = {0};
  image foreground;
  image background;
  
  foreground.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  background.resize(src.getNumberOfRows(), src.getNumberOfColumns());
      
      //gets histogram of image
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
              histoarr[src.getPixel(i,j)] = histoarr[src.getPixel(i,j)] + 1;      
              
         }   
      }
      
      //thresholds the src image
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
              if(src.getPixel(i,j) >= T)
              {
                foreground.setPixel(i,j,src.getPixel(i,j));
              }
              else if(src.getPixel(i,j) < T) 
              {
                background.setPixel(i,j,src.getPixel(i,j));
              }
         }   
      }
      
   
    char x = *G;
   // cout << endl <<x;
    //applies histogram stretch to background
    if(x == 'B')
    {
      
        utility::histostretch(background, tgt, A,B); 
       
        for(int i=0; i<src.getNumberOfRows(); i++)
        {
      
          for(int j=0; j<src.getNumberOfColumns(); j++)
          {
              if(src.getPixel(i,j) >= T)
              {
                tgt.setPixel(i,j,src.getPixel(i,j));           
              }

          }   
        } 
        
    }
    //applies histogram stretch to foreground
    else if(x == 'F')
    {
        utility::histostretch(foreground,tgt,A,B);
        
        for(int i=0; i<src.getNumberOfRows(); i++)
        {
      
          for(int j=0; j<src.getNumberOfColumns(); j++)
          {
              if(src.getPixel(i,j) < T)
              {
                //gets original image back onto stretched foreground image.
                tgt.setPixel(i,j,src.getPixel(i,j));          
              }

          }   
        }
        
        
    }

}

/*-------------------------------------------------------------------------*/
void utility::colorstretch(image &src, image &tgt, char* C, int A, int B)
{
  //tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  char color = *C; 
  //stretch for Red channel 
  if(color == 'R')
  {
      tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
      float histoarr[256] = {0};
      
        for(int i=0; i<src.getNumberOfRows(); i++)
        {
        
           for(int j=0; j<src.getNumberOfColumns(); j++)
           {
                //gets histogram of red values in image  
                histoarr[src.getPixel(i,j,RED)] = histoarr[src.getPixel(i,j,RED)] + 1;                
           }   
        }
        
      float Imin = 0;
      float Imax = 0;
      int pos = 0;

      //getting min position in hist
      for(int i = 0; i<256; i++)             
      {
       if(histoarr[i] == 0)
       {
           pos++;
       }
       else
         break;
      }
     
     Imin = pos;  //C
     
     pos = 255;

     //getting max position in hist
     for(int i = 255; i>0; i--)           
     {
       if(histoarr[i] == 0)
       {
           pos--;
       }
       else
         break;
     }
  
      Imax = pos;       //D
      
      int P;
    
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
            //histogram stretching equation applied
            P = (src.getPixel(i,j,RED) - Imin)*((B-A)/(Imax-Imin)) + A;      
             tgt.setPixel(i,j,RED,P);
             tgt.setPixel(i,j,GREEN,(src.getPixel(i,j,GREEN)));
             tgt.setPixel(i,j,BLUE,(src.getPixel(i,j,BLUE))) ;
         }   
      } 
    
  }
  //stretch for Green channel
  else if(color == 'G')
  {
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
      float histoarr[256] = {0};
      
        for(int i=0; i<src.getNumberOfRows(); i++)
        {
        
           for(int j=0; j<src.getNumberOfColumns(); j++)
           {    
                //gets histogram of Green values in image
                histoarr[src.getPixel(i,j,GREEN)] = histoarr[src.getPixel(i,j,GREEN)] + 1;                 
           }   
        }
        
      float Imin = 0;
      float Imax = 0;
      int pos = 0;
      //getting min position in hist
      for(int i = 0; i<256; i++)             
      {
       if(histoarr[i] == 0)
       {
           pos++;
       }
       else
         break;
      }
     
     Imin = pos;  //C
     
     pos = 255;
     //getting max position in hist
     for(int i = 255; i>0; i--)           
     {
       if(histoarr[i] == 0)
       {
           pos--;
       }
       else
         break;
     }
  
      Imax = pos;       //D
      
      float P;
    
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
            //histogram stretching equation applied
            P = (src.getPixel(i,j,GREEN) - Imin)*((B-A)/(Imax-Imin)) + A;      
             tgt.setPixel(i,j,RED,(src.getPixel(i,j,RED)));
             tgt.setPixel(i,j,GREEN,P);
             tgt.setPixel(i,j,BLUE,(src.getPixel(i,j,BLUE))) ;
         }   
      }
    
  }
  //stretch for Blue channel
  else if(color == 'B')
  {
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
      float histoarr[256] = {0};
      
        for(int i=0; i<src.getNumberOfRows(); i++)
        {
        
           for(int j=0; j<src.getNumberOfColumns(); j++)
           {
                //gets histogram of Blue values in image
                histoarr[src.getPixel(i,j,BLUE)] = histoarr[src.getPixel(i,j,BLUE)] + 1;                 
           }   
        }
        
      float Imin = 0;
      float Imax = 0;
      int pos = 0;
      for(int i = 0; i<256; i++)             
      {
       if(histoarr[i] == 0)
       {
           pos++;
       }
       else
         break;
      }
     
     Imin = pos;  //C
     
     pos = 255;
      for(int i = 255; i>0; i--)           
     {
       if(histoarr[i] == 0)
       {
           pos--;
       }
       else
         break;
     }
  
      Imax = pos;       //D
      
      float P;
    
      for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
            //histogram stretching equation applied for blue channel
            P = (src.getPixel(i,j,BLUE) - Imin)*((B-A)/(Imax-Imin)) + A;      
             tgt.setPixel(i,j,RED,(src.getPixel(i,j,RED)));
             tgt.setPixel(i,j,GREEN,(src.getPixel(i,j,GREEN)));
             tgt.setPixel(i,j,BLUE,P);
         }   
      }

  
  }
  
}

/*-------------------------------------------------------------------------*/
void utility::rgbtohsi(image &src, image &tgt)
{
  
   tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
  // ivec.resize(src.getNumberOfRows() * src.getNumberOfColumns());
   
     for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {

              double R = src.getPixel(i,j,RED);
              double G = src.getPixel(i,j,GREEN);
              double B = src.getPixel(i,j,BLUE);
              
              double x;
              double h,s,v;
              double H,S,I;
              if(R==0 && G==0 && B== 0)
              {
                H=0;
                S=0;
                I=0;
              }
              else{
               double r = (R/(R+G+B));   //normalizing
               double g = (G/(R+G+B));
               double b = (B/(R+G+B));
                
               I =((R+G+B)/(3*255)); 
           
               S = 1 - (3/(r+g+b)) * min(min(r,g),b);
   
                  if(b<=g){
                     H = acos((0.5*((r-g) + (r-b))) / (pow(pow((r-g),2) + (r-b)*(g-b), 0.5)));
                  }
                  else if(b>g){
                      H = (2*M_PI) - acos((0.5 *((r-g)+(r-b))) /  (pow(pow((r-g),2) + (r-b)*(g-b), 0.5)));  
                  }

              }          
          //converting to ranges[0,360] [0,100] [0,255]
          H = (H*180)/M_PI;
          S = S*100;
          I = I*255;

          tgt.setPixel(i,j,RED,H);
          tgt.setPixel(i,j,GREEN,S);
          tgt.setPixel(i,j,BLUE,I);              
        
         }   
         
      }  

}

/*-------------------------------------------------------------------------*/
void utility::hsistretch(image &src, image &tgt, int A, int B) 
{
 //src needs to be rgb then converted to hsiimage// right now only works with hsi input
 image hsisrc;
 hsisrc.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 //utility::rgbtohsi(src,hsisrc);
 image hsi, htg, org ,ngl, shsi;
 //src = hsisrc;
 //src.save("newsrc.ppm");
   //org stores original h,s values
   org = src;  

  htg.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
        // I value used for grey level image stored in blue channel
        int pixelSize = src.getPixel(i,j,BLUE);      
        //storing gray level image to htg
        htg.setPixel(i,j,RED,pixelSize);
        htg.setPixel(i,j,GREEN,pixelSize);
        htg.setPixel(i,j,BLUE,pixelSize);
    
      }
		}
   // htg.save("htg.pgm");

   //applying histogram stretch to new gray level image
   tgt.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
   float histoarr[256] = {0};
   int count =0;
      for(int i= 0; i<htg.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<htg.getNumberOfColumns(); j++)
         {
              //gets histogram of image htg
              histoarr[htg.getPixel(i,j)] = histoarr[htg.getPixel(i,j)] + 1;   
             
         }   
      }
 
  
   float Imin = 0;
   float Imax = 0;
   int pos = 0;
   //getting min position in hist
   for(int i = 0; i<256; i++)     
   {
     if(histoarr[i] == 0)
     {
        pos++;
     }
     else
       break;
   }
   
   Imin = pos;  //C
   
   pos = 255;
   //getting max position in hist
   for(int i = 255; i>0; i--)           
   {
     if(histoarr[i] == 0)
     {
         pos--;
     }
     else
       break;
   }
    Imax = pos;       //D
    
    float P;
    //stretch grey level image and store stretched image into ngl
    ngl.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
    for(int i=0; i<htg.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<htg.getNumberOfColumns(); j++)
         {
             P = (htg.getPixel(i,j) - Imin)*((B-A)/(Imax-Imin)) + A;  
                  
             //cout << P << endl;
             ngl.setPixel(i,j,RED,P);
             ngl.setPixel(i,j,GREEN,P);    
             ngl.setPixel(i,j,BLUE,P);     
         }   
      }
     // ngl.save("ngl.pgm");
      //turning stretched grey level image back into hsi
      shsi.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
      for(int i=0; i<org.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<org.getNumberOfColumns(); j++)
         {
           //new stretched hsi image stored as shsi
           shsi.setPixel(i,j,RED,org.getPixel(i,j,RED));
           shsi.setPixel(i,j,GREEN,org.getPixel(i,j,GREEN));  
           shsi.setPixel(i,j,BLUE,ngl.getPixel(i,j,BLUE));
         }   
      }
     // shsi.save("shsi.ppm");
      //convert back into rgb
      utility::hsitorgb(shsi,tgt);

} 

void utility::hsistretchnorm(image &src, image &tgt) 
{
 //src needs to be rgb then converted to hsiimage// right now only works with hsi input
 image hsisrc;
 hsisrc.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 //utility::rgbtohsi(src,hsisrc);
 image hsi, htg, org ,ngl, shsi;
 //src = hsisrc;
 //src.save("newsrc.ppm");
   //org stores original h,s values
   org = src;  

  htg.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
        // I value used for grey level image stored in blue channel
        int pixelSize = src.getPixel(i,j,BLUE);      
        //storing gray level image to htg
        htg.setPixel(i,j,RED,pixelSize);
        htg.setPixel(i,j,GREEN,pixelSize);
        htg.setPixel(i,j,BLUE,pixelSize);
    
      }
		}
   // htg.save("htg.pgm");

   //applying histogram stretch to new gray level image
   tgt.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
   float histoarr[50000] = {0};
   int count =0;
      for(int i= 0; i<htg.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<htg.getNumberOfColumns(); j++)
         {
              //gets histogram of image htg
              histoarr[htg.getPixel(i,j)] = histoarr[htg.getPixel(i,j)] + 1;   
             
         }   
      }
 
  
   float Imin = 0;
   float Imax = 0;
   int pos = 0;
   //getting min position in hist
   for(int i = 0; i<50000; i++)     
   {
     if(histoarr[i] == 0)
     {
        pos++;
     }
     else
       break;
   }
   
   Imin = pos;  //C
   
   pos = 49000;
   //getting max position in hist
   for(int i = 49000; i>0; i--)           
   {
     if(histoarr[i] == 0)
     {
         pos--;
     }
     else
       break;
   }
    Imax = pos;       //D
    
    float P;
    //stretch grey level image and store stretched image into ngl
    ngl.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
    for(int i=0; i<htg.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<htg.getNumberOfColumns(); j++)
         {
             P = (htg.getPixel(i,j) - Imin)*((255-0)/(Imax-Imin)) + 0;      
            // cout << P << endl;
             ngl.setPixel(i,j,RED,P);
             ngl.setPixel(i,j,GREEN,P);    
             ngl.setPixel(i,j,BLUE,P);     
         }   
      }
     // ngl.save("ngl.pgm");
      //turning stretched grey level image back into hsi
      shsi.resize(htg.getNumberOfRows(), htg.getNumberOfColumns());
      for(int i=0; i<org.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<org.getNumberOfColumns(); j++)
         {
           //new stretched hsi image stored as shsi
           shsi.setPixel(i,j,RED,org.getPixel(i,j,RED));
           shsi.setPixel(i,j,GREEN,org.getPixel(i,j,GREEN));  
           shsi.setPixel(i,j,BLUE,ngl.getPixel(i,j,BLUE));
         }   
      }
     // shsi.save("shsi.ppm");
      //convert back into rgb
      utility::hsitorgb(shsi,tgt);

} 

/*-------------------------------------------------------------------------*/
void utility::hsitorgb(image &src, image &tgt)
{
    
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());

    for(int i=0; i<src.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<src.getNumberOfColumns(); j++)
         {
              double H = src.getPixel(i,j,RED);
              double S = src.getPixel(i,j,GREEN);
              double I = src.getPixel(i,j,BLUE);
              
              
              double x,y,z;
              double R,G,B;

              H = (H * M_PI)/180;
              S = (S/100);
              I = (I /255);
             
              x = I * (1-S);
              y = I * (1+((S*cos(H))/(cos((M_PI/3)-H)))); 
              z = 3*I - (x + y);
            
              if(H == 0){
                R = I + 2*I*S;
                G = I - I*S;
                B = I - I*S;
              }
              else if(H < (2*M_PI)/3 && H > 0)   
              {
                B = x;
                R = y;
             
                G = z; 
              }
              else if(H == (2*M_PI)/3){
                  R = I - I*S;
                  G = I + 2*I*S; 
                  B = I - I*S;
              }
              else if(((2*M_PI)/3) < H && ((4*M_PI)/3 > H))   
              {
                R = x;
              
                y =  I * (1+((S*cos(H-((2*M_PI)/3)))/(cos((M_PI)-H))));
               
                G = y;
                B = (3*I) - (R + G);
               
              }
              else if(H == (4*M_PI)/3){
                R = I - I*S;
                G = I - I*S;
                B = I + 2*I*S;
              }
              else if(((4*M_PI)/3) < H && (2*M_PI) > H)  //<=
              {
                
                G = x;
              
                y =  I * (1+((S*cos(H-((4*M_PI)/3)))/(cos(((5*M_PI)/3)-H))));
               
                B = y;
                R = (3*I) - (G + B);
               
              }
              
              R=R*255;

              G=G*255;


              B=B*255;
             

              tgt.setPixel(i,j,RED,R);
              tgt.setPixel(i,j,GREEN,G);
              tgt.setPixel(i,j,BLUE,B);
          }
      }
    
  

}

/*-------------------------------------------------------------------------*/
void utility::sobel3(image &src, image &tgt){

  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=1; i< src.getNumberOfRows()-1; i++)
	{
		for (int j=1; j< src.getNumberOfColumns()-1; j++)
		{	
			 
        int Gx = 0;
        int Gy = 0;
        int intensity = 0;
        char* pixel;
      
        //left column
        intensity = src.getPixel(i-1,j-1);       
        Gx += -intensity;
        Gy += -intensity;
        
        intensity = src.getPixel(i-1,j);
        Gx += -2 * intensity;
                     
        intensity = src.getPixel(i-1,j+1); 
        Gx += -intensity;
        Gy += +intensity;                          
        
        //middle column
        intensity = src.getPixel(i,j-1);
        Gy += -2 * intensity;
        
        intensity = src.getPixel(i,j+1);
        Gy += +2 *intensity;                 
        
        
        //right column
        intensity = src.getPixel(i+1,j-1);
        Gx += +intensity;
        Gy += -intensity;
        
        intensity = src.getPixel(i+1,j);
        Gx += +2 * intensity;
        
        intensity = src.getPixel(i+1,j+1);
        Gx += +intensity;
        Gy += +intensity;
        
        //calculate gradient length
        unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
        
        
        tgt.setPixel(i,j, length); 
                   
		}
   
	}
 
image final; 

utility::histostretchnorm(tgt, final); // test if works and then move onto dual thresholding

tgt = final;

final.save("sobel3.pgm");


}

/*-------------------------------------------------------------------------*/
void utility::sobel5(image &src, image &tgt)
{
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=2; i< src.getNumberOfRows()-2; i++)
	{
		for (int j=2; j< src.getNumberOfColumns()-2; j++)
		{	
			 
        int Gx = 0;
        int Gy = 0;
        int intensity = 0;
       
        intensity = src.getPixel(i-2,j-2);       
        Gx += -5 *intensity;
        Gy += -5* intensity ;
        
        intensity = src.getPixel(i-2,j-1);
        Gx += -8 * intensity;
        Gy += -4 * intensity;
                     
        intensity = src.getPixel(i-2,j); 
        Gx += -10 * intensity;
        //Gy += +intensity;                           
        
        intensity = src.getPixel(i-2,j+1);
        Gx += -8 * intensity;
        Gy += 4 * intensity;
        
        intensity = src.getPixel(i-2,j+2);
        Gx += -5 * intensity;
        Gy += 5 * intensity;
        
        // column 2
        intensity = src.getPixel(i-1,j-2);
        Gx += -4 * intensity;
        Gy += -8 * intensity;
        
        intensity = src.getPixel(i-1,j-1);
        Gx += -10 * intensity;
        Gy += -10 * intensity;
        
        intensity = src.getPixel(i-1,j);
        Gx += -20 * intensity;
        //Gy += -10 * intensity;
        
        intensity = src.getPixel(i-1,j+1);
        Gx += -10 * intensity;
        Gy += 10 * intensity;
        
        intensity = src.getPixel(i-1,j+2);
        Gx += -4 * intensity;
        Gy += 8 * intensity;
        
        //middle column
        intensity = src.getPixel(i,j-2);
        //Gx += -10 * intensity;
        Gy += -10 * intensity;
        
        intensity = src.getPixel(i,j-1);
        //Gx += -10 * intensity;
        Gy += -20 * intensity;
        
        intensity = src.getPixel(i,j+1);
        //Gx += -10 * intensity;
        Gy += 20 * intensity;
        
        intensity = src.getPixel(i,j+2);
        //Gx += -10 * intensity;
        Gy += 10 * intensity;
       
        //collumn 4
        intensity = src.getPixel(i+1,j-2);
        Gx += 4 * intensity;
        Gy += -8 * intensity;
        
        intensity = src.getPixel(i+1,j-1);
        Gx += 10 * intensity;
        Gy += -10 * intensity; 
        
        intensity = src.getPixel(i+1,j);
        Gx += 20 * intensity;
        //Gy += -10 * intensity; 
        
        intensity = src.getPixel(i+1,j+1);
        Gx += 10 * intensity;
        Gy += 10 * intensity;
        
        intensity = src.getPixel(i+1,j+2);
        Gx += 4 * intensity;
        Gy += 8 * intensity;
          
                
        //right column
        intensity = src.getPixel(i+2,j-2);
        Gx += 5 * intensity;
        Gy += -4 * intensity;
        
        intensity = src.getPixel(i+2,j-1);
        Gx += 8 * intensity;
        Gy += -4 * intensity;
        
        intensity = src.getPixel(i+2,j);
        Gx += 10 * intensity;
       // Gy += -4 * intensity;
        
        intensity = src.getPixel(i+2,j+1);
        Gx += 8 * intensity;
        Gy += 5 * intensity;
        
        intensity = src.getPixel(i+2,j+2);
        Gx += 5 * intensity;
        Gy += 4 * intensity;
        
        
        //calculate gradient length
        unsigned int length = (unsigned int)sqrt( (float)(Gx * Gx) + (float)(Gy * Gy) );
        
     
        
        tgt.setPixel(i,j, length); 
        
        
                   
		}
   
	}
 
image final;

utility::histostretchnorm(tgt, final); //normalizes  new function must be added with set a b values

tgt = final;

final.save("sobel5.pgm");


}

/*-------------------------------------------------------------------------*/
void utility::binaryedge(image &src, image &tgt, int TH, int TL)
{
  //sobel filter was applied before hand in iptool.cpp  
  tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i< src.getNumberOfRows(); i++)
	{
		for (int j=0; j< src.getNumberOfColumns(); j++)
		{	
        //dual thresholding for image with sobel filter applied to binarize 
        if(src.getPixel(i,j) > TH)
        {
            tgt.setPixel(i,j,255);
        }
        else if(src.getPixel(i,j) < TL)
        {
            tgt.setPixel(i,j,0);
        }
        //
        else if(src.getPixel(i,j) < TH && src.getPixel(i,j) > TL)
        {
           int window = 0;
           int neighborflag = 0;
           int isEdge = 0;
           window = (3-1) /2;
           
           if( i < window || j <window ||(i >= (src.getNumberOfRows()-window) || (i >=(src.getNumberOfColumns() - window )))) //change to j
           neighborflag =1;
          
          if(neighborflag == 0)
          {
              for(int k = -window; k <=window; k++)
              {
                for(int l = -window; l <= window; l++)
                {
                    if(tgt.getPixel(i+k,j+l) ==255)
                    isEdge = 1;
                
                }
              }
            if(isEdge == 1)
            {
              tgt.setPixel(i,j,255);
            }
          
          }
        }
        
    }
    
  }  
  
 tgt.save("binaryedge.pgm");
 image blank;
 image horizontal;
 image slant45deg;
 src = tgt;
 //tgt = blank;
 //tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 horizontal.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 slant45deg.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 //angle calculation for horizontal edge and 45 degree edge.
 for (int i=1; i< src.getNumberOfRows()-1; i++)
	{
		for (int j=1; j< src.getNumberOfColumns()-1; j++)
		{	
        //gets gradient for angle calculation    
        int Gx = 0;
        int Gy = 0;
        int intensity = 0;
        char* pixel;
      
        //left column
        intensity = src.getPixel(i-1,j-1);        
        Gx += -intensity;
        Gy += -intensity;
        
        intensity = src.getPixel(i-1,j);
        Gx += -2 * intensity;
                     
        intensity = src.getPixel(i-1,j+1); 
        Gx += -intensity;
        Gy += +intensity;                           
        
        //middle column
        intensity = src.getPixel(i,j-1);
        Gy += -2 * intensity;
        
        intensity = src.getPixel(i,j+1);
        Gy += +2 *intensity;                 
        
        
        //right column
        intensity = src.getPixel(i+1,j-1);
        Gx += +intensity;
        Gy += -intensity;
        
        intensity = src.getPixel(i+1,j);
        Gx += +2 * intensity;
        
        intensity = src.getPixel(i+1,j+1);
        Gx += +intensity;
        Gy += +intensity;
 
       int angle;
       //angle equation
       angle = atan2(Gx,Gy)* 180/ M_PI;
       
       //cout << angle << endl;
       
       //binarizes for 45 degrees
       if(angle >= 35 && angle <= 55)
       {
         slant45deg.setPixel(i,j,255);
       
       }
       else
         slant45deg.setPixel(i,j,0);
         
       //binarizes for horizontal
       if(angle <= 100 && angle >= 80)  
       {
         horizontal.setPixel(i,j,255);
       }
       else
         horizontal.setPixel(i,j,0);
       
   }
        
  }
  
  slant45deg.save("45deg.pgm");  
  
  horizontal.save("horizontal.pgm");
  
}

void utility::roi(image &src, image &tgt, int x, int y, int Sx, int Sy, int flag)
{
    //gets three strings for the roi output file name
    char img1[MAXLEN];
     char img2[MAXLEN];
     char img3[MAXLEN];
     
     if(flag == 0)
     {
        strcpy(img1,"applylast.pgm");
        strcpy(img2, "applysecond.pgm");
        strcpy(img3,"applyfirst.pgm");
     }
     else if(flag == 1)
     {
       strcpy(img1,"applylast.ppm");
       strcpy(img2, "applysecond.ppm");
       strcpy(img3,"applyfirst.ppm");
     
     }
     //resize the params
  tgt.resize(Sy,Sx);
  
  
  int k = 0, l = 0;
	for (int i=x; i<(Sx + x); i++)     
	{
    k = 0;
		for (int j=y; j<(Sy + y); j++)       
		{
      
      int pixelSize = src.getPixel(j,i);    
      if(flag == 0)
      {
		    tgt.setPixel(k,l,pixelSize);
      }
      else if(flag == 1)
      {
       int pixelSizeR = src.getPixel(j,i,RED);
       int pixelSizeG = src.getPixel(j,i,GREEN);
       int pixelSizeB = src.getPixel(j,i,BLUE);
        tgt.setPixel(k,l,RED,pixelSizeR);
        tgt.setPixel(k,l,GREEN,pixelSizeG);
        tgt.setPixel(k,l,BLUE,pixelSizeB);
      }
      k = k + 1;
		}
    l = l + 1;
	}
   src = tgt;
   

}

void utility::histoMake(image &tgt)   //grey scale only
{
      float histoarr[256] = {0};
      //creates array for histogram
      for(int i=0; i<tgt.getNumberOfRows(); i++)
      {
      
         for(int j=0; j<tgt.getNumberOfColumns(); j++)
         {
              histoarr[tgt.getPixel(i,j)] = histoarr[tgt.getPixel(i,j)] + 1;   
              
         }

        
      }

      int max = histoarr[0];
      int min = histoarr[0];
     
      for(int i=0;i < 256; i++)      
      {
          if(max < histoarr[i])
          {
            max = histoarr[i];     
          }
          
          if(min > histoarr[i])
          {
            min = histoarr[i];
          }
      }
    

      for(int i=0; i<256; i++)
      {
        histoarr[i] = (histoarr[i] - min) / (max - min);   //normalize array
      
      }
   
       
       image histogram(512,512);    
       for(int i=0; i<histogram.getNumberOfRows();i++)
       {
        for(int j=0;j<histogram.getNumberOfColumns();j++)           //sets backgroud to white
          {
              histogram.setPixel(i,j,255);
          
          }
       }
      
      
     
      int x = 0;
       for(int i=0; i<histogram.getNumberOfColumns();i++)          //sets bars in histogram
       {
           
           float iter = histoarr[x] * 256;
           
           if((i%2)==1){
               x++;              //width of bar  2 pixels
             }
             
           iter = 512 - iter;         // sets pixels towrds the bottom poition
         
                    
       
          for(int j = iter; j<512; j++)
          {
                  
               histogram.setPixel(j,i,0);
          
          }
          
      }
      
     histogram.save("histogram.pgm");


}

void utility::combineMod(image &src, image &tgt, image &m1, int* arr, int colorFlag) // arr first   m1 
{
     char img1[MAXLEN];
     char img2[MAXLEN];
     char img3[MAXLEN];
     
     if(colorFlag == 0)
     {
        strcpy(img1,"applylast.pgm");
        strcpy(img2, "applysecond.pgm");
        strcpy(img3,"applyfirst.pgm");
     }
     else if(colorFlag == 1)
     {
       strcpy(img1,"applylast.ppm");
       strcpy(img2, "applysecond.ppm");
       strcpy(img3,"applyfirst.ppm");
     
     }
    tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());  
  //  tgt = src;
   
    int roiflag = 0;
    int x= 0;
    int y= 0;
    for (int i=0; i<src.getNumberOfRows(); i++)
	  {
       roiflag = 0;
		  for (int j=0; j<src.getNumberOfColumns(); j++)
		  {
        if((i >= arr[1] && i < (arr[1] + arr[3])) && (j >= arr[0] && j < (arr[0] + arr[2])))        
        {
          roiflag = 1;
        }
        else
        {
          roiflag = 0;
        } 
        
        
        if(roiflag == 1)  //is in roi use modfied image
        {
          if(colorFlag == 0)
          {
            tgt.setPixel(i, j, m1.getPixel(x, y));
          }
          else
          {
            tgt.setPixel(i, j, RED, m1.getPixel(x, y,RED));
            tgt.setPixel(i, j, GREEN, m1.getPixel(x, y,GREEN));
            tgt.setPixel(i, j, BLUE, m1.getPixel(x, y,BLUE));
          }
         // y++;
          y = y + 1;
        }
        else if(roiflag == 0)  //is not roi use src image
        {
          if(colorFlag == 0)
          {
          tgt.setPixel(i,j, src.getPixel(i,j));
          }
          else
          {
            tgt.setPixel(i, j, RED, src.getPixel(i, j,RED));
            tgt.setPixel(i, j, GREEN, src.getPixel(i, j,GREEN));
            tgt.setPixel(i, j, BLUE, src.getPixel(i, j,BLUE));
          
          }
        }
      }
      if(y > 0)
        x = x+1;
        
        
      y = 0;
      
    }
   
}

void utility::colorbright(image &src, image &tgt, int DR, int DG, int DB){  //
 
 tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
 for (int i=0; i<src.getNumberOfRows(); i++)   
 {                      
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{  
      int pixelSize1 = src.getPixel(i,j,RED);
      int pixelSize2 = src.getPixel(i,j,GREEN);
      int pixelSize3 = src.getPixel(i,j,BLUE);
			tgt.setPixel(i,j,RED,(pixelSize1*DR));
      tgt.setPixel(i,j,GREEN,(pixelSize2*DG));
      tgt.setPixel(i,j,BLUE,(pixelSize3*DB));  
      
		}
  } 
 
 } 

/*------------------------------------------------------------------------*/
void utility::dualthres(image &src, image &tgt,int T, int V1, int V2)  
{
  
   tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
   for (int i=0; i<src.getNumberOfColumns(); i++)
   {
      for(int j = 0; j<src.getNumberOfColumns(); j++)
      {
          int PixelB = src.getPixel(i,j);
          
          if(src.getPixel(i,j) < T){
              PixelB = src.getPixel(i,j) - V2;
              if(PixelB < 0){
                PixelB = 0;
              }
          }
          else if(src.getPixel(i,j) > T){
              PixelB = src.getPixel(i,j) + V1;
              if(PixelB > 255){
                PixelB = 255;
              }
          
         }
          tgt.setPixel(i,j,PixelB);
            
      }
   }
  

}

/*-----------------------------------------------------------------------*/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			/* Map the pixel of new image back to original image */
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				/* Directly copy the value */
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				/* Average the values of four pixels */
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}
