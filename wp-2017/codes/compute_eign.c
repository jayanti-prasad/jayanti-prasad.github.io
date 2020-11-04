/*--------------------------------------------------------------------
  This program computes the eign values and eign vectors of matrix
  using the GSL libraries.
  
  The matrix for which the eign values & eign vectors are calculated,
  has to be given at the run time in a '.mat' file.

  This program has a test part also which makes sure that you get the 
  correct answers.
  
  
  Jayanti Prasad, April 27, 2011
  
  Commments & Suggestion : prasad.jayanti@gmail.com		
  
  -------------------------------------------------------------------- */

#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

int test_eign(int , double [], double [], double[]); 

int  main (int argc, char *argv[])    {
  double *data,*data1; 
  FILE *inpf;
  int i, j,ndim; 
 
  if (argc < 2){
    fprintf(stderr,"./compute_inverse <matrix file>\n");
    return(-1);  
  }
 
  inpf=fopen(argv[1],"r");
  fscanf(inpf,"%d\n",&ndim);
  data=(double *)malloc(ndim*ndim*sizeof(double));
  data1=(double *)malloc(ndim*ndim*sizeof(double));

  for(i=0; i < ndim; i++){
    for(j=0; j < ndim; j++){
      fscanf(inpf,"%lf",&data[j+ndim*i]);
        data1[j+ndim*i]=data[j+ndim*i];
       }
    fscanf(inpf,"\n");
    
  }
  fclose(inpf);
 
 
  gsl_matrix_view m = gsl_matrix_view_array (data, ndim, ndim);
  // fill the matrix for which eign values/vectors are computed
  
  gsl_vector *eval  = gsl_vector_alloc (ndim);
  // a vector which contains the eign values 

  gsl_matrix *evec  = gsl_matrix_alloc (ndim, ndim);
  // a mtrix colums of which are eign vectors 
  
  gsl_eigen_symmv_workspace * w =  gsl_eigen_symmv_alloc (ndim);
  // this is just for work space 
  
  gsl_eigen_symmv (&m.matrix, eval, evec, w);
  // pass the matrix to main engine and get back the 
  // eign values and eign vectors 
  
  gsl_eigen_symmv_free (w);
  
  gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_ABS_ASC);
  
  // this section writies out put i.e., eign values & vectors, one by one 
  

  printf(" ----- Eign values \n");
  for(i=0; i < ndim ; i++)
    printf(" %2.6f ",gsl_vector_get(eval,i));
  printf("\n ---- Eign Vectors (Columns) \n");

  for(i=0; i < ndim; i++){
    for(j=0; j < ndim; j++)
      printf(" %2.6f ",gsl_matrix_get(evec,i,j));
    printf("\n");
  
  }
  printf("\n");
 

  { 
  double P[ndim*ndim],lambda[ndim];

  for(i=0; i < ndim; i++)
     lambda[i] = gsl_vector_get(eval,i); 
  for(i=0; i < ndim; i++)
    for(j=0; j < ndim; j++)
    P[j+ndim*i] = gsl_matrix_get(evec,i,j); 
 
  test_eign(ndim,lambda,data1,P);
}

  gsl_vector_free (eval);
  gsl_matrix_free (evec);
 
  return 0;
}

int test_eign(int ndim, double l[], double A[], double  P[]){
  int i, j, k; 
  double  *I,*B,*X,*Y;
  I=(double *)malloc(ndim*ndim*sizeof(double));
  B=(double *)malloc(ndim*ndim*sizeof(double));
  Y=(double *)malloc(ndim*sizeof(double));
  X=(double *)malloc(ndim*sizeof(double));

 printf("-------Checking -----------------------------\n"); 

  for(i=0; i < ndim; i++){
   for(j=0; j < ndim; j++){
     if (i==j)
        I[j+ndim*i]=1.0;
     else
        I[j+ndim*i]=0.0; 
   }
  }

  for(i=0; i < ndim; i++){ 
      for(j=0; j < ndim ; j++){
        for(k=0; k < ndim ; k++){
          B[k+ndim*j]=A[k+ndim*j]-I[k+ndim*j] *l[i];
       }
    }

   for(j=0; j < ndim ; j++)
       X[j]=P[i+ndim*j];


   for(j=0; j < ndim; j++){
       Y[j] = 0.0;
      for(k=0; k < ndim; k++){
        Y[j] += B[k+ndim*j] * X[k];       
    }
   }

  printf("Eign Value=%2.6f\n",l[i]); 
  printf("Eign Vector =  (" );
  for(j=0; j < ndim ; j++)
       printf("  %2.6f ",X[j]);
   printf(")\n" );

  printf("Residual:  (A-lambda *I)*X = (" );
  for(j=0; j < ndim ; j++)
       printf("  %2.6f ",Y[j]);
   printf(")\n" );
}

  return(0); 
}




