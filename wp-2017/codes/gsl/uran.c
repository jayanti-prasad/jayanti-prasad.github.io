/*-------------------------------------------------------------

This program demonstrate the use GSL for generating  
Uniform Random Numbers in range [0-1] 

            - Jayanti Prasad, Sept 13, 2011    
              Comments & Feedback : prasad.jayanti@gmail.com 
-------------------------------------------------------------*/
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>

int  main (int argc, char *argv[]){
  const gsl_rng_type * T;
  gsl_rng * r;
  int i, n;
  double u; 
  
  if (argc < 2){
   fprintf(stderr,"./uran <#  points>\n");
   return(-1); 
  }

  n = atoi(argv[1]);
  gsl_rng_env_setup();
  
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  
  for (i = 0; i < n; i++)    {
     u = gsl_rng_uniform (r);
     printf ("%.6f\n", u);
    }
  
  gsl_rng_free (r);
  
  return 0;
}

