/*----------------------------------------------------------------
  This program show the use of 1d complex Fourier transformation using 
  FFTW3.
  
  Note that the input data must be in the following form :
  1d : x, Re(f(x)),Im(f(x))
  
  For comments and suggestions mail to prasad.jayanti@gmail.com
  Jayanti Prasad 
  Dec 04, 2013  
  -----------------------------------------------------------------*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<fftw3.h> 
// fftw3.h must be included
#include<complex.h>
// complex.h is needed for complex numbers 

int modes(int , float []);

int main(int argc, char *argv[]) {
  int i, n;
  fftw_complex *X,*X1,*Y; 
  fftw_plan p,q; 
  FILE *fp1,*fp2;
  float *x,*f,t2,t3,C,f_nyq,dx; 
  
  if (argc < 2){
    fprintf(stderr,"./example_dft_1d  <input file> <size along one dim>\n");
    return(-1);
  }
  
  fp1 = fopen(argv[1],"r");
  n   = atoi(argv[2]);
  C   = 1.0/n;
  
  X  = fftw_alloc_complex(n);
  X1 = fftw_alloc_complex(n);
  Y  = fftw_alloc_complex(n);
  
  // Note that fftw_alloc_complex is equivalent to (fftw_complex *)
  
  x = (float *)malloc(n*sizeof(float));
  f = (float *)malloc(n*sizeof(float));
  
  for(i=0; i < n; i++){
    fscanf(fp1,"%f %f %f\n",&x[i],&t2,&t3);
    X[i][0] = t2;
    X[i][1] = t3;
  }
  fclose(fp1);

  modes(n,f);
  
  dx = (x[n-1]-x[0])/(n-1); 
  f_nyq = 1.0/(2.0*dx);

  // The frequnecy range must be [-f_nyq,f_nyq] which corresponds to [0,n-1] or [-n/2,n/2]
  // note that n/2 corresponds to both +f_nyq and -f_nyq check Numerical Recepies 
  
  for(i=0; i < n; i++)
    f[i] *=2.0*f_nyq;  
  
  p = fftw_plan_dft_1d(n, X,Y, FFTW_FORWARD, FFTW_ESTIMATE); 
  fftw_execute(p); 
  
  q=fftw_plan_dft_1d(n, Y, X1, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(q);
  
  fp1=fopen("out_1d.dat","w");
  fp2=fopen("rec_1d.dat","w");
 
  for(i=0; i < n; i++){
    fprintf(fp1,"%.6f   %.6e  %.6e\n",f[i],Y[i][0],Y[i][1]);
    fprintf(fp2,"%.6f   %.6e  %.6e\n",x[i],C*X1[i][0],C*X1[i][1]);
  }
  fclose(fp1);
  fclose(fp2);
  

  free(x);
  free(f);
  
  fftw_free(X);
  fftw_free(X1); 
  fftw_free(Y);  
  
  return(0);
  
}
