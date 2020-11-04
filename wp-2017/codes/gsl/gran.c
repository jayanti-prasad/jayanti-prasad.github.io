/*-------------------------------------------------------------

This program demonstrate the use GSL for generating  
Gassian Random Numbers in range [0-1] 

           - Jayanti Prasad, Sept 13, 2011    
             Comments & Feedback : prasad.jayanti@gmail.com 
--------------------------------------------------------------*/
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

int  main (int argc, char *argv[]){
  const gsl_rng_type * T;
  gsl_rng * r;
  int i, n;
  double sigma,g;

  if (argc < 3){
     fprintf(stderr,"./gran <#  points> <sigma> \n");
      return(-1);
  }
  
  n = atoi(argv[1]);
  sigma=atoi(argv[2]); 

  gsl_rng_env_setup();
  
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  
  for (i = 0; i < n; i++) {
     g = gsl_ran_gaussian (r,sigma); 
     fprintf(stdout,"%.6f\n", g);
    }
  
  gsl_rng_free (r);
  
  return 0;
}

