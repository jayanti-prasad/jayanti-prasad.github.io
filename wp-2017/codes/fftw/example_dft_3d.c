#include<stdio.h>
#include<stdlib.h>
#include<fftw3.h>
#include<math.h>
#include<complex.h>
#include <omp.h>

int modes(int ,float []);

int main (int argc, char *argv[]){
  fftw_complex *X, *X1, *Y;  
  fftw_plan p,  q; 
  int i, j, k,l,i1,j1,k1, n;
  FILE *fp1,*fp2;
  float *x,*y,*z,*fx,*fy,*fz,C,t1,t2,f_nyq,dx; 

  if (argc < 2){
    fprintf(stderr,"./example_dft_3d  <input file> <size along one dim>\n");
    return(-1);
  }

  fp1=fopen(argv[1],"r");
  n=atoi(argv[2]);

  printf("max threads=%d\n",omp_get_max_threads());

  fftw_init_threads();
  fftw_plan_with_nthreads(omp_get_max_threads());
  //fftw_plan_with_nthreads(8);

  X  = fftw_alloc_complex(n*n*n);
  X1 = fftw_alloc_complex(n*n*n);
  Y  = fftw_alloc_complex(n*n*n);
 
  x=(float *)malloc(n*n*n*sizeof(float));
  y=(float *)malloc(n*n*n*sizeof(float));
  z=(float *)malloc(n*n*n*sizeof(float));

  fx=(float *)malloc(n*sizeof(float));
  fy=(float *)malloc(n*sizeof(float));
  fz=(float *)malloc(n*sizeof(float));

  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      for(k=0; k < n; k++){
        l = k+n*(j+n*i); 
	fscanf(fp1,"%f %f %f %f %f\n",&x[l],&y[l],&z[l],&t1,&t2);
        X[l][0] = t1; 
        X[l][1] = t2; 
      }
    }
  }
  fclose(fp1);
 
  modes(n ,fx);
  modes(n ,fy);
  modes(n ,fz);
  C = 1.0/(n*n*n); 

  dx = (x[n*n*n-1]-x[0])/(n-1);
  f_nyq = 1.0/(2.0*dx);

 printf("f_nyq=%.6f\n",f_nyq);

  // The frequnecy range must be [-f_nyq,f_nyq] which corresponds to [0,n-1] or [-n/2,n/2]
  // note that n/2 corresponds to both +f_nyq and -f_nyq check Numerical Recepies 

  for(i=0; i < n; i++){
    fx[i] *=2.0*f_nyq;
    fy[i] *=2.0*f_nyq;
    fz[i] *=2.0*f_nyq;
 }

  p=fftw_plan_dft_3d(n,n,n, X, Y, FFTW_FORWARD, FFTW_ESTIMATE);  
  fftw_execute(p); 
  
  // This is the inverse fourier transform 
    
  q=fftw_plan_dft_3d(n,n,n, Y, X1, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(q); 
  
  fp1=fopen("out_3d.dat","w");
  fp2=fopen("rec_3d.dat","w");
  
  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      for(k=0; k < n; k++){
        l = k+n*(j+n*i);   
	fprintf(fp1,"%.6f %.6f %.6f %.6e %.6e\n",fx[i],fy[j],fz[k],Y[l][0],Y[l][1]);
	fprintf(fp2,"%.6f %.6f %.6f %.6f %.6f\n",x[l],y[l],z[l],C*X1[l][0],C*X1[l][1]);
      }
    }
  }
 
  free(x);
  free(y);
  free(z);

  free(fx);
  free(fy);
  free(fz); 

  fftw_free(X);
  fftw_free(Y);
  fftw_free(X1);



  fclose(fp1);
  fclose(fp2);
  
  return(0);
  
  
}
