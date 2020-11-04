#include <stdio.h>
#include <gsl/gsl_rng.h>

int  main (int argc, char *argv[]){
  const gsl_rng_type * T;
  gsl_rng * r;
  float x,sigma;   
  int i, n, itype;
 
  fprintf(stdout,"Give the number of Points \n");
  scanf("%d",&n); 	
    
  fprintf(stdout,"Give 0  for Uniform & 1 for Gaussian  Random Number\n");
  scanf("%d",&itype); 
  
  if (itype == 1){ 
    fprintf(stdout,"give the sigma\n");
    scanf("%f",&sigma);
    printf("sigma=%.6f\n",sigma);
  }
 
 
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

    
  for (i = 0; i < n; i++) {
    if (itype ==1 ){ 
      x = gsl_ran_gaussian (r,0.1);
      printf("%.6f\n",x);
    }else
      x = gsl_rng_uniform (r);
    
//    fprintf (stdout,"%.5f\n", (float)sigma);
  }
  
  gsl_rng_free (r);
  
  return 0;
}

