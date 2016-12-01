#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 

using namespace std;
using namespace cv;

Mat base;  //declaration de notre base
 #define N_max 4  // La norme pour la quelle les points appartiennent a la fractale
 #define iter_max 150 
 #define HEI 600
 #define WID 800   // taille de l'image

std::complex<long double> c (-0.7927,0.1609 );  // valeur de la constante complexe c        
void mainthread(); // thread principale
void secondthread();// threads secondaire

 void mainthread()
{
  for(int x=0;x<WID;x++){
      for(int y=0;(y<HEI/4);y++){
// conversion de notre base de -1=>1 est faite par le calcul (-1+(x*WID/2))
long double X1= ((long double)-1 +((long double)x *((long double)2/(long double)WID))); // calcul de la nouvelle valeur des pixels dans la bsse(-1;1)
long double Y1= ((long double)-1 +((long double)y *((long double)2/(long double)HEI)));
 std::complex<long double> ZC(Y1,X1); 
      
 int iteration=0;
        long double norm = std::norm(ZC);
        while(iteration<iter_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }


        if(iteration==iter_max && norm<N_max){ // défintion de la couleur de la couleur de l'image 
          base.at<Vec3b>(x,y)[0]=180; 
          base.at<Vec3b>(x,y)[1]=180; 
          base.at<Vec3b>(x,y)[2]=180;
        }
       else{
          int couleur=(int)((float)iteration/(float)iter_max*255);// definitions des couleurs de la fractale
          base.at<Vec3b>(x,y)[0]=couleur/10;
          base.at<Vec3b>(x,y)[1]=couleur/10;
          base.at<Vec3b>(x,y)[2]=couleur;
      
      }
    }
  } 

}

// creation des threads secondaires



 void* secondthread(void* p)
{

 int ident = *((int*) p);

  for(int x=0;x<WID;x++){
      for(int y=ident*(HEI/4);y<((ident+1)*(HEI/4));y++){

long double X1= ((long double)-1 +((long double)x *((long double)2/(long double)WID)));
long double Y1= ((long double)-1 +((long double)y *((long double)2/(long double)HEI)));
 std::complex<long double> ZC(Y1,X1); 
      
 int iteration=0;
        long double norm = std::norm(ZC);
        while(iteration<iter_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }


        if(iteration==iter_max && norm<N_max){
          base.at<Vec3b>(x,y)[0]=180; 
          base.at<Vec3b>(x,y)[1]=180; 
          base.at<Vec3b>(x,y)[2]=180;
        }
       else{
          int couleur=(int)((float)iteration/(float)iter_max*255);
          base.at<Vec3b>(x,y)[0]=couleur/10;
          base.at<Vec3b>(x,y)[1]=couleur/10;
          base.at<Vec3b>(x,y)[2]=couleur;
      
      }
    }
  } 
}

int main( int argc, char** argv ){
  pthread_t ID[3];  
  int tab[3]={1,2,3};

base=cv::Mat(WID, HEI, CV_8UC3);

  for(int k=0;k<3;k++)   // création d'un compteur qui vas parcourir les 3 threads secondaire
    pthread_create(&ID[k], NULL,secondthread,(void*) &tab[k]); // creations des threads secondaires
  
  mainthread(); // appel du thread principale

  for(int k=1;k<3;k++)
    pthread_join(ID[k], NULL);// appel des thread secondaires
   
  while( true ) {	 
    imshow("picture julia", base ); 
    if(cvWaitKey(30) > 0){
      break;
    }
  }

  return 0;
}



 
