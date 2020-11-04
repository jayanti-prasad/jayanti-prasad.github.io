/*---------------------------------------------------------
  This program computes the determinant of  matrix using GSL.
  
  Input matrix must be passed in a file at runtime and should 
  in the '.mat' format (which I use for all matrix algebra). 

                                Jayanti Prasad, Sept 21, 2011
                Feedback & Comments : prasad.jaaynti@gmail.com 
----------------------------------------------------------- */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>

int main(int argc, char *argv[]){
  int i, j, ndim, signum;
  float  *A;
  FILE *fp;
  gsl_matrix * B;
  gsl_permutation * p;
  double det; 
  
  if (argc < 2){
    fprintf(stderr,"./compute_det  <input file>\n");
    return(-1);
  }
  
  fp = fopen(argv[1],"r");
  fscanf(fp,"%d\n",&ndim);
  A = (float *)malloc(ndim*ndim*sizeof(float));
  for(i=0; i < ndim; i++){
    for(j=0; j < ndim; j++)
      fscanf(fp," %f",&A[j+ndim*i]);
    fscanf(fp,"\n");
  }
  fclose(fp);
  
  B =  gsl_matrix_alloc (ndim, ndim);
  p =  gsl_permutation_alloc(ndim);
  
  printf("A=\n");
  for(i=0; i < ndim; i++){
    for(j=0; j < ndim; j++){
      printf(" %2.6e ",A[j+ndim*i]);
      gsl_matrix_set(B,i,j,A[j+ndim*i]);
    }
    printf("\n");
  }
  
  gsl_linalg_LU_decomp (B,p,&signum);
 
  det = 1.0; 
  for(i=0; i < ndim; i++){
    for(j=0; j < ndim; j++){
      if (i==j)
	det*=gsl_matrix_get(B,i,j); 
      
    }
    printf("\n");
  }
  
  if (signum < 0.0)
    det *=-1.0;  
  
  printf("|A|= %2.6e\n",det); 
  gsl_permutation_free(p);
  gsl_matrix_free(B);
    
  return(0);
}
