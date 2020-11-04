#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <stdio.h>
#include <gsl/gsl_blas.h>


int main(int argc, char *argv[]){
  double *a,*b,*c;
  gsl_matrix_view A ,B,C;
  int i, j, ndim1,ndim2;
  FILE *fp1,*fp2; 
  
  if(argc < 3) {
    fprintf(stderr,"./compute_multi <A.mat > <B.mat>\n"); 
    return(-1); 
  }
  
  fp1=fopen(argv[1],"r");
  fp2=fopen(argv[2],"r");
  fscanf(fp1,"%d\n",&ndim1);
  fscanf(fp2,"%d\n",&ndim2);
  
  a=(double  *)malloc(ndim1*ndim1*sizeof(double));
  b=(double  *)malloc(ndim1*ndim1*sizeof(double));
  c=(double  *)malloc(ndim1*ndim1*sizeof(double));

  if(ndim1 !=ndim2){
    fprintf(stderr,"Error ! matrix not compatible !\n");
    return(-1); 
  }
  
  for(i=0; i < ndim1;i++){ 
    for(j=0; j < ndim1; j++){
      fscanf(fp1," %lf ",&a[j+ndim1*i]);
      fscanf(fp2," %lf ",&b[j+ndim1*i]);
    }
    fscanf(fp1,"\n"); 
    fscanf(fp2,"\n"); 
  }
  
  A = gsl_matrix_view_array(a, ndim1, ndim1);
  B = gsl_matrix_view_array(b, ndim1, ndim1);
  C = gsl_matrix_view_array(c, ndim1, ndim1);
  
  /* Compute C = A B */
  
  gsl_blas_dgemm (CblasNoTrans,CblasNoTrans,1.0,&A.matrix, &B.matrix,0.0,&C.matrix);
  

 fprintf(stderr,"--------------A-------------------------\n");
 for(i=0; i < ndim1;i++){
    for(j=0; j < ndim1; j++){
      fprintf(stderr," %2.6f ",a[j+ndim1*i]);
    }
    fprintf(stdout,"\n");
  }
 fprintf(stderr,"--------------B-------------------------\n");

 for(i=0; i < ndim1;i++){
    for(j=0; j < ndim1; j++){
      fprintf(stderr," %2.6f ",b[j+ndim1*i]);
    }
    fprintf(stdout,"\n");
  }
 fprintf(stderr,"--------------C=AXB----------------------\n");
 
  fprintf(stdout,"%d\n",ndim1);
  for(i=0; i < ndim1;i++){ 
    for(j=0; j < ndim1; j++){
      fprintf(stdout," %2.6f ",c[j+ndim1*i]);
    }
    fprintf(stdout,"\n"); 
  }
  

 
 return 0;  
}

