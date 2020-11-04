#include<stdio.h>
#include<fftw3.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>

int modes(int ,float []);

int main(int argc, char *argv[]) {
  fftw_complex *X, *Y,*X1; 
  fftw_plan p,q;
  int i, j, n;
  FILE *fp1,*fp2,*fp3;
  float *x,*y,*fx,*fy,C1,t1,t2,dx,f_nyq;

  if (argc < 2){
    fprintf(stderr,"./example_dft_2d  <input file> <size along one dim>\n");
    return(-1);
  }

  fp1=fopen(argv[1],"r");
  n = atoi(argv[2]);
  
  x=(float *)malloc(n*n*sizeof(float));
  y=(float *)malloc(n*n*sizeof(float)); 
  fx =(float *)malloc(n*sizeof(float)); 
  fy =(float *)malloc(n*sizeof(float)); 


  X  = fftw_alloc_complex(n*n);
  X1 = fftw_alloc_complex(n*n);
  Y  = fftw_alloc_complex(n*n);

  for (i=0; i < n; i++){
    for(j=0; j < n; j++){
      fscanf(fp1,"%f %f %f %f\n",&x[j+n*i],&y[j+n*i],&t1,&t2);
      X[j+n*i][0]=t1;
      X[j+n*i][1]=t2;
    }
  }
  fclose(fp1);

  modes(n ,fx);
  modes(n ,fy);

  dx = (x[n*n-1]-x[0])/(n-1);
  f_nyq = 1.0/(2.0*dx);


  // The frequnecy range must be [-f_nyq,f_nyq] which corresponds to [0,n-1] or [-n/2,n/2]
  // note that n/2 corresponds to both +f_nyq and -f_nyq check Numerical Recepies 

  for(i=0; i < n; i++){
    fx[i] *=2.0*f_nyq;
    fy[i] *=2.0*f_nyq;
 }
 
  p=fftw_plan_dft_2d(n,n,X,Y, FFTW_FORWARD, FFTW_ESTIMATE); 
  fftw_execute(p); 
  
  q=fftw_plan_dft_2d(n,n,Y,X1, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(q);
  
  fftw_destroy_plan(p);
  fftw_destroy_plan(q);

  fp1=fopen("out_2d.dat","w");
  fp2=fopen("rec_2d.dat","w");
  
  C1=1.0/(n*n);

  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      fprintf(fp1,"%.6f %.6f %.6f %.6f\n",fx[i],fx[j],Y[j+n*i][0],Y[j+n*i][1]);
      fprintf(fp2,"%.6f %.6f %.6f %.6f\n",x[j+n*i],y[j+n*i],C1*X1[j+n*i][0],C1*X1[j+n*i][1]);
    }
  }
  fclose(fp1);
  fclose(fp2);

  free(fx);
  free(fy);
  free(x);
  free(y);

  fftw_free(X); 
  fftw_free(Y); 
  fftw_free(X1);  

  return(0);
}
