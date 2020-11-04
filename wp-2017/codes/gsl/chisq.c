#include <stdio.h>
#include <gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>
#include<gsl/gsl_cdf.h>

int  main (int argc, char *argv[]){
  int i, n;
  double x1,x2,x,y,nu; 
  
  if (argc < 4){
     fprintf(stderr,"./chisq  <nu> <# points> <xmin> <xmax>\n");
     return(-1); 
  }

  nu = atof(argv[1]);
  n  = atoi(argv[2]); 
  x1 = atof(argv[3]);
  x2 = atof(argv[4]);
    
  for (i = 0; i < n; i++)    {
       x = x1 + ((double) i /n)*(x2-x1); 
       y = gsl_ran_chisq_pdf(x,nu);
     printf ("%.6f %.6f\n",x,y);
    }
  
  
  return 0;
}

