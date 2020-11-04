/*----------------------------------------------------------------
   This program creates the input data for the 1, 2 and 2-d complex
   Fourier transformation examples which are supplied using FFTW3.


   Note that the input data must be in the following form :
   1d : x, Re(f(x)),Im(f(x))
   2d : x, y, Re(f(x,y)),Im(f(x,y))
   3d : x, y,z, Re(f(x,y,z)),Im(f(x,y,z))
   
   For comments and suggestions mail to prasad.jayanti@gmail.com
   Jayanti Prasad 
   Dec 04, 2013  
   -----------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define X_MIN -10.0
#define X_MAX  10.0

#define Y_MIN -10.0
#define Y_MAX  10.0

#define Z_MIN -10.0
#define Z_MAX  10.0

int main(int argc, char *argv[]){
  float x,y,z,X,Y,dx,k_nyq,ks;
  int i, j, k,n;  
  FILE *fp1,*fp2,*fp3;

  if (argc < 2){
    fprintf(stderr,"./create_data <# points along one dim>\n");
    return(-1);
  }	

  n =  atoi(argv[1]);
  
  fp1=fopen("data_dft_1d.dat","w");
  fp2=fopen("data_dft_2d.dat","w");
  fp3=fopen("data_dft_3d.dat","w");
  
  dx = (X_MAX-X_MIN)/(n-1); 
  
  k_nyq  = 1/(2.0*dx); // This is the nyqyest frequnecy 
  ks = k_nyq/8.0;
  
  printf("k_nyq=%.6f ks=%.6f\n",k_nyq,ks);
  
  for(i=0; i < n; i++){
    x=X_MIN + (float) i * dx;
    X = sin(2.0*M_PI*ks*x)+sin(2.0*M_PI*2.0*ks*x);
    Y = 0.0;
    fprintf(fp1,"%.6f %.6f %.6f\n",x,X,Y);

    for(j=0; j < n; j++){
      y=Y_MIN + (float) j * (Y_MAX-Y_MIN)/(n-1);
      X = sin(2.0*M_PI*ks*x)+sin(2.0*M_PI*2.0*ks*x);
      Y = 0.0;
      fprintf(fp2,"%.6f %.6f %.6f %.6f\n",x,y,X,Y);
      for(k=0; k < n; k++){
	z=Z_MIN + (float) k * (Z_MAX-Z_MIN)/(n-1);
	X = sin(2.0*M_PI*ks*x)+sin(2.0*M_PI*2.0*ks*x);
	Y = 0.0;
	fprintf(fp3,"%.6f %.6f %.6f %.6f %.6f\n",x,y,z,X,Y);
      }
    }
    
  } 
  
  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  
  return(0); 
}
