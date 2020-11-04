#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

int  main (int argc, char *argv[])    {
     int i,j,ndim;
     FILE *fp;
     float *X;
      
     fp=fopen(argv[1],"r");
     fscanf(fp,"%d",&ndim);
     X=(float *)malloc(ndim*ndim*sizeof(float)); 

     for(i=0; i < ndim ; i++){ 
       for(j=0; j < ndim; j++){
         fscanf(fp,"%f",&X[j+ndim*i]); 
      }
      fscanf(fp,"\n"); 
     }
     fclose(fp); 


     gsl_vector *S  = gsl_vector_alloc (ndim);
     gsl_vector *work  = gsl_vector_alloc (ndim);

     gsl_matrix *A  = gsl_matrix_alloc (ndim, ndim);
     gsl_matrix *V  = gsl_matrix_alloc (ndim, ndim);

    for(i=0; i < ndim; i++){
        for(j=0; j < ndim; j++)
           gsl_matrix_set (A, i, j, X[j+ndim*i]);
    }

     gsl_linalg_SV_decomp (A,V,S,work);


    printf("U\n");
    for(i=0; i < ndim ; i++){
       for(j=0; j < ndim; j++){
         printf("%6.2f",gsl_matrix_get (A, i, j));
      }
      printf("\n");
     }

   printf("V\n");
    for(i=0; i < ndim ; i++){
       for(j=0; j < ndim; j++){
         printf("%6.2f",gsl_matrix_get (V, i, j));
      }
      printf("\n");
     }

   printf("S\n");
   for(j=0; j < ndim; j++)
         printf("   %6.2f   ",gsl_vector_get (S,j));
   printf("\n");


     return 0;
 }



