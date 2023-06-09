/*-------------------------------------------------------------
This program demonstrate the use GSL for binning 
data for making histograms.

This program takes the minimum value, maximum value, number 
of bins on command line.

The input file is passed through stdin.

         - Jayanti Prasad, Sept 13, 2011    
           Comments & Feedback : prasad.jayanti@gmail.com 
-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_histogram.h>

int main (int argc, char **argv){
  double a, b;
  size_t n;
  
  if (argc != 4)    {
    printf ("Usage: gsl-histogram xmin xmax n\n"
	    "Computes a histogram of the data "
	    "on stdin using n bins from xmin "
	    "to xmax\n");
    fprintf(stderr,"./histogram x1 x2 nbin < ur.dat \n");
    exit (0);
  }
  
  a = atof (argv[1]);
  b = atof (argv[2]);
  n = atoi (argv[3]);
  
  {
    double x;
    gsl_histogram * h = gsl_histogram_alloc (n);
    gsl_histogram_set_ranges_uniform (h, a, b);
    
    while (fscanf (stdin, "%lg", &x) == 1)
      {
	gsl_histogram_increment (h, x);
      }
    gsl_histogram_fprintf (stdout, h, "%g", "%g");
    gsl_histogram_free (h);
  }
  exit (0);
}

