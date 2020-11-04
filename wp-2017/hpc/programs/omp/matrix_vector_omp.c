#include <stdio.h>
#include <stdlib.h>

int  mxv(int,int,double [], double [], double []);

int nthreads; 

int main(int argc, char *argv[]){
  double *a,*b,*c;
  int i, j, m, n;
  
  if (argc < 4){
    fprintf(stderr,"./a.out <nthreads> <m> <n>\n");
    return(-1);
  }
  
  nthreads = atoi(argv[1]);
  m = atoi(argv[2]);
  n = atoi(argv[3]);
  
  a=(double *)malloc(m*sizeof(double));
  b=(double *)malloc(m*n*sizeof(double));
  c=(double *)malloc(n*sizeof(double));

  for (j=0; j<n; j++)
    c[j] = 2.0;
 
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      b[i*n+j] = i;
  
  mxv(m, n, a, b, c);
  
  /*
  printf("Matrix B :\n");
  for (i=0; i<m; i++){
    for (j=0; j<n; j++){
      printf("%.2f ",b[i*n+j]);
    }
    printf("\n");
  }

  printf("Vector C :\n");
  for (j=0; j<n; j++){
    printf("%.2f ",c[j]);
  
  }
    printf("\n");
  
  printf("Vector A = B * C:\n");
  for (j=0; j<n; j++){
    printf("%.2f ",a[j]);
  
  }
  printf("\n");
  */

  free(a);
  free(b);
  free(c);
  
  return(0);
}

int  mxv(int m, int n, double a[], double b[], double c[]){
  int i, j;
  
  omp_set_num_threads(nthreads); 

#pragma omp parallel for default(none)   shared(m,n,a,b,c) private(i,j)
  for (i=0; i<m; i++) {
      a[i] = 0.0;
      for (j=0; j<n; j++)
	a[i] += b[i*n+j]*c[j];
  } 

}
