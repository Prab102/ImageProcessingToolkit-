
#include "../iptools/core.h"
#include <strings.h>
#include <string.h>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
  //creates images obj
	image src, tgt, temp, NEWTMP;
  image mod1,mod2,mod3;
  //file pointer
	FILE *fp;
  //strTOK initializer
	char str[MAXLEN];
  // text for an outfile
	char outfile[MAXLEN];
  //char string to get input from params
	char *pch;
  //IF FILE CANNOT BE OPENED
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}
  //WHILE FILE IS NOT EMPTY
	while(fgets(str,MAXLEN,fp) != NULL) {
    //gets the name of the image file to read
		pch = strtok(str, " ");
		src.read(pch);

 
		pch = strtok(NULL, " ");
    //gets the file name of the output file
		strcpy(outfile, pch);
  
   string filetype;
   //Gets whether the file is a ppm or pgm
   filetype = pch;
   filetype = filetype.substr(filetype.size()-3);
   int fileflag;
   if(filetype == "ppm")
   {
      fileflag = 1; 
   }
   else if(filetype =="pgm")
   {
     fileflag = 0;
   
   }

   //creates 3 arrays for the params of the ROI(Region of Interest)
   int first[4] = {0};
   int second[4] = {0};
   int third[4] = {0};
   

    //gets the number of ROI
    int roiNum =atoi(strtok(NULL," ")); 
    int roiCount = roiNum; 
    
     //IF roiNum is greater than 3 or less than 1 exit code 
     if(roiNum > 3 || roiNum < 1){
     
       cout << "not a valid numebr of ROIs";
       return 1;
     }
      temp = src;
     //WHILE roiNum is not equal to 0
     while(roiNum != 0){
    
       
       //getting the roi params
       int x = atoi(strtok(NULL," "));
       int y = atoi(strtok(NULL," ")); 
       int Sx = atoi(strtok(NULL," "));
       int Sy = atoi(strtok(NULL," "));
       
       //gets name of function called
       char* func = strtok(NULL," ");


       //ROI bound checking
       if(src.isInbounds(Sy,Sx) != 1)  
       {
         cout << "roi is out of bounds";
         return 1;
       }
       if(src.getNumberOfRows() <= x || src.getNumberOfColumns() <= y || src.getNumberOfRows() < (Sy + y) || src.getNumberOfColumns() < (Sx + x))   //sy y -> sx x
       {
         cout << "roi is out of bounds";
         return 1;
       }
       if(Sx == 0 || Sy == 0) 
       {
          cout << "cannot be 0";
          return 1;
       
       }
       
       //setting roi params to respective arrays 
       if(roiNum == 1)  // add last
       {
         first[0] = x;
         first[1] = y;
         first[2] = Sx;
         first[3] = Sy;
       }
       
      else if(roiNum == 2)
       {
         second[0] = x;
         second[1] = y;
         second[2] = Sx;
         second[3] = Sy;
       }
       else if(roiNum == 3)
       {
         third[0] = x;
         third[1] = y;
         third[2] = Sx;
         third[3] = Sy;
       
       }
       image newIMG;
       utility::roi(src,tgt,x,y,Sx,Sy,fileflag);
       tgt = newIMG;
      
    //  src.save("fileroi.ppm"); //test
                   
       //function checks
       if(strcmp(func,"add")==0)
       {
        //one parameter, intensity to add
         int param1 = atoi(strtok(NULL," ")); 
         utility::addGrey(src,tgt,param1);
      
       }
       else if(strcmp(func,"binarize") == 0)
       {
         //one parameter threshold value
         int param1 = atoi(strtok(NULL," "));   
         utility::binarize(src,tgt,param1);
         
       }
        else if(strcmp(func,"reg2dsmooth")== 0) 
       {
         //one parameter window size 3 or 5
         int param1 = atoi(strtok(NULL," ")); 
         if (param1 != 3 && param1 != 5){
            cout << "Window size can only be 3 or 5" <<endl; 
            return 0;
         }
         utility::reg2dsmooth(src,tgt,param1);
       }
       else if(strcmp(func,"dualthres")==0)
       {
          int param1 = atoi(strtok(NULL," "));
          int param2 = atoi(strtok(NULL," "));
          int param3 = atoi(strtok(NULL," "));
          utility::dualthres(src,tgt,param1,param2,param3);

       }
       else if(strcmp(func,"scale")==0)
       {
          int param1 = atoi(strtok(NULL," "));
          utility::scale(src,tgt,param1);
       }

        else if(strcmp(func,"sep2dsmooth") == 0) //remove
       {
      //   cout << "this is sep2dsmooth";  //one parameter
         int param1 = atoi(strtok(NULL," "));   // window size
       }
       
        else if(strcmp(func,"colorbright") == 0)
       {
         //three parameter
         int param1 = atoi(strtok(NULL," "));   //DR
         int param2 = atoi(strtok(NULL," "));   //DG
         int param3 = atoi(strtok(NULL," "));   //DB
         utility::colorbright(src,tgt,param1,param2,param3); 
         
       }
        else if(strcmp(func,"colorvisual") == 0)  
       {
         //two parameter
         int param1 = atoi(strtok(NULL," "));    //threshold
         int param2 = atoi(strtok(NULL," "));    //V1
         utility::colorvisual(src,tgt,param1,param2);
       }
       else if(strcmp(func,"histostretch") == 0)                                    
       {
         //two parameter     
         int param1 = atoi(strtok(NULL," "));    //A lower range value
         int param2 = atoi(strtok(NULL," "));    //B higher range value
         utility::histostretch(src,tgt, param1, param2);
       }
       else if(strcmp(func,"histostretchnorm") == 0)  //histogram equalization default
       {
         utility::histostretchnorm(src,tgt);
       }
       else if(strcmp(func,"histothres") == 0)
       {
         //four parameter
         int param1 = atoi(strtok(NULL," "));  //threshold
         char *param2 = strtok(NULL," ");      //background or foreground to apply histo stretching
         int param3 = atoi(strtok(NULL," "));  //A lower range value
         int param4 = atoi(strtok(NULL," "));  //B higher range value
        
         utility::histothres(src,tgt,param1,param2,param3,param4);
       }
       else if(strcmp(func,"colorstretch") == 0)
       {
         //3 params
         char* param1 = strtok(NULL," ");      //color range  double check
         int param2 = atoi(strtok(NULL," "));  //A
         int param3 = atoi(strtok(NULL," "));  //B
        
         utility::colorstretch(src,tgt,param1,param2,param3);
       }
       else if(strcmp(func,"rgbtohsi") == 0) 
       {
        //use before hsistretch function  
        utility::rgbtohsi(src,tgt);
         
       }
       else if(strcmp(func,"hsitorgb") == 0) 
       {
        //used for testing, used in hsistretch
        utility::hsitorgb(src,tgt);
         
       }
       else if(strcmp(func,"hsistretch") == 0) 
       {
         
         int param1 = atoi(strtok(NULL," "));  //A lower range value 
         int param2 = atoi(strtok(NULL," "));  //B higher rage value
         utility::hsistretch(src,tgt,param1,param2);
         
       }
       else if(strcmp(func,"hsistretchnorm") == 0)  
       {
         //uses 0 256 as default A B
         utility::hsistretchnorm(src,tgt);
         
       }
       else if(strcmp(func,"sobel3")==0) {  

        utility::sobel3(src,tgt);

      }
      else if(strcmp(func,"sobel5")==0) { 

        utility::sobel5(src,tgt); //window size 5 for filter
        
      }
      else if(strcmp(func,"binaryedge")==0) { 

        int p1;
        int p2;
        image blank;
        
        pch = strtok(NULL," ");
        p1 = atoi(pch);              
        
        pch = strtok(NULL," ");
        p2 = atoi(pch);                  
        
        //apply sobel filter for better clearer result
        utility::sobel3(src,tgt);
        
        src = tgt;
        tgt = blank;
        
        utility::binaryedge(src,tgt, p1, p2);
        
      }
       //if incorrect function name  
       else{
         cout << " function input is invalid";
         return 0;
       }
     //file names for roi  
     char img1[MAXLEN];
     char img2[MAXLEN];
     char img3[MAXLEN];
     
     //checks for file type
     if(fileflag == 0)   
     {
        strcpy(img1,"applylast.pgm");
        strcpy(img2, "applysecond.pgm");
        strcpy(img3,"applyfirst.pgm");
     }
     else if(fileflag == 1)
     {
       strcpy(img1,"applylast.ppm");
       strcpy(img2, "applysecond.ppm");
       strcpy(img3,"applyfirst.ppm");
     
     }
       //saves 3 images for each possible roi
       if(roiNum == 1)            
       {
         tgt.save(img1);
        //last saved;
         mod1.read(img1); 
       
       }  
       else if(roiNum ==2)
       {
        //mid saved
         tgt.save(img2); 
         mod2.read(img2);
     
       }
       else if(roiNum == 3)
       {
         tgt.save(img3); 
         mod3.read(img3);
       }     
       
       src = temp;
       roiNum--;
     } //End of while for roi
     

     tgt = NEWTMP;
     tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns()); 
     
     //adding the possible modified ROIs to the original image    
     while(roiCount != 0)
     {
      
        if(roiCount == 3){
     
           utility::combineMod(src,tgt, mod3, third,fileflag);  
       }
      
       else if(roiCount == 2){
      
           utility::combineMod(src,tgt, mod2, second,fileflag);
       }
      
       else if(roiCount == 1){
       
           utility::combineMod(src,tgt, mod1, first,fileflag);
       }
     
     src = tgt;
     
     roiCount--;
   }
		tgt.save(outfile);
	}
	fclose(fp);
	return 0;
}

