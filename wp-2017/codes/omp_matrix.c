#include<stdio.h>
#include<omp.h>

int l=10, m=10,n=10;
float vmulti(int,float[],float[]); 

int main(int argc, char *argv[]){
   int i,j,k,nthreads = 2;
   float A[l*m],B[l*m],C[l*m],D[l],E[l]; 
   for(i = 0; i < l ; i++){
      for(j=0; j < m; j++){
        A[j+m*i] = (float) i;
	B[j+m*i] = (float) j; 
	C[j+m*i] = 0.0;
      }
   }   

   omp_set_num_threads(nthreads);   

#pragma omp parallel for shared (A,B,C,i) private (D,E,j,k)     
   for (i=0; i < l; i++){
     for (j=0; j < n; j++){
      for(k=0; k < m; k++){
         D[k] = A[k+m*i];
         E[k] = B[j+l*k]; 
      }
      C[j+n*i] = +vmulti(m,D,E); 
     }
   } 

  printf("A=\n");  
  for(i=0; i < l ; i++){
     for(j=0; j < m; j++){
        printf("%2.0f",A[j+m*i]); 
     }
    printf("\n");  
  }

  printf("B=\n");
  for(i=0; i < m ; i++){
     for(j=0; j < n; j++){
      printf("%2.0f",B[j+n*i]);
      }
    printf("\n");
  }

  printf("C=\n");
  for(i=0; i < l ; i++){
      for(j=0; j < n; j++){
        printf("%2.0f ",C[j+n*i]);
       }
      printf("\n");
    }
   return(0); 
}


float vmulti(int p, float A[], float B[]){
  float x;
  int i;
  x = 0.0;
  for(i=0; i < p; i++)
     x+=A[i] * B[i]; 
  return(x); 
}

