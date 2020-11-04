/* --------------------------------------------------------- */
/* -  This program demonstrate the use of GSL in fitting a straight  */
/*    line to data set (which is in the form of three columns, named */
/*    independent varibale, dependent variable and the error). */
/* -  Apart from computing the best fit parameters it also computes */
/*    chi^2 and covriance matrix. */
/*                          Jayanti Prasad, April 12, 2011  */
/* ----------------------------------------------------------- */
#include <stdio.h>
#include <gsl/gsl_fit.h>
int main (int argc, char *argv[])
{
  int i, n;
  double *x,*y,*w; 
  double c0, c1, cov00, cov01, cov11, chisq;
  FILE *inpf; 
  
  if (argc < 2){
    fprintf(stderr,"use as follows\n");
    fprintf(stderr,"./fitline filename \n");
    return(0);
  }
  
  x=(double *)malloc(sizeof(double));
  y=(double *)malloc(sizeof(double));
  w=(double *)malloc(sizeof(double));
  
  inpf = fopen(argv[1],"r");
  n = 0;
  while(!feof(inpf)){
    fscanf(inpf,"%lf %lf %lf\n",&x[n],&y[n],&w[n]);
    n++;
    x=realloc(x,(n+1)*sizeof(double));
    y=realloc(y,(n+1)*sizeof(double));
    w=realloc(w,(n+1)*sizeof(double));
  }
  
  
  gsl_fit_wlinear (x, 1, w, 1, y, 1, n,
		   &c0, &c1, &cov00, &cov01, &cov11,
		   &chisq);
  
  printf ("# best fit: Y = %g + %g X\n", c0, c1);
  printf ("# covariance matrix:\n");
  printf ("# [ %g, %g\n#   %g, %g]\n",
	  cov00, cov01, cov01, cov11);
  printf ("# chisq = %g\n", chisq);
  
  return(0);     
  

}

