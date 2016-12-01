#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 

using namespace std;
using namespace cv;

Mat base;;
 #define N_max 4
 #define iter_max 150
 #define HEI 600
 #define WID 800   // taille de l'image

std::complex<long double> c (-0.7927,0.1609 );          

 void fractale()
{
  for(int x=0;x<WID;x++){
      for(int y=0;y<HEI;y++){
// conversion de nore base de -1=>1
long double X1= ((long double)-1 +((long double)x *((long double)2/(long double)WID)));
long double Y1= ((long double)-1 +((long double)y *((long double)2/(long double)HEI)));
 std::complex<long double> ZC(Y1,X1); // nouvelle representation de pixel
      
 int iteration=0;
        long double norm = std::norm(ZC);
        while(iteration<iter_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }


        if(iteration==iter_max && norm<N_max){// definition de la couleur de l'image
         base.at<Vec3b>(x,y)[0]=180; 
          base.at<Vec3b>(x,y)[1]=180; 
          base.at<Vec3b>(x,y)[2]=180;
        }
       else{
          int couleur=(int)((float)iteration/(float)iter_max*255);
          base.at<Vec3b>(x,y)[0]=couleur/10;   // definitions de la couleur de la fractale
          base.at<Vec3b>(x,y)[1]=couleur/10;
          base.at<Vec3b>(x,y)[2]=couleur;
      
      }
    }
  }
}

int main( int argc, char** argv )
{
  base=cv::Mat(WID, HEI, CV_8UC3);

    
    fractale();
     while( true )
     {
     	 
	     imshow("dessin FRACTALE",base ); 
     cvReleaseImage(&fcopy);  
        cvDestroyWindow("dessin FRACTALE"); 
     	 if(cvWaitKey(5) > 0){
        break;
       }
}
 
  return 0;
}




 
