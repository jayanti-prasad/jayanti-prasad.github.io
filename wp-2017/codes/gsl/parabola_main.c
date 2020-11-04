/*------------------------------------------------------------
  This program demonstare fitting 'ax**2+bx*c' to a data set
  which is created in the program itself.
  Jayanti Prasad, April 14, 2011
  ------------------------------------------------------------- */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>

#define N 100

#include "parabola.c"

void print_state (size_t iter, gsl_multifit_fdfsolver * s);

int main(int argc, char *argv[]){
  int status;
  size_t n = N,p=3;
  const gsl_multifit_fdfsolver_type *T;
  gsl_multifit_fdfsolver *s;
  gsl_multifit_function_fdf f;
  const gsl_rng_type * type,T1;
  gsl_matrix *covar = gsl_matrix_alloc(p,p);
  gsl_rng * r,*r1;
  double x_init[3] = {1.0, 1.0, 1.0}; // this is initial guess
  gsl_vector_view x = gsl_vector_view_array (x_init,p);
  unsigned int i,j,k,iter = 0;
  double tt,tt1,tt2,tt3,*C,*C0;
  double xx[N], y[N], sigma[N];
  struct data d = {n,xx,y,sigma};
  double c1=2.1,c2=7.4,c3=5.67; // these are the exact values 
  double xmax=10.0,alpha=1.0; // range [-xmax,xmax] in x and amplitude of noise
  FILE *inpf;
  
  gsl_rng_env_setup();
  
  type = gsl_rng_default;
  r = gsl_rng_alloc (type);
  
  for(i=0; i < n; i++){
    double u = gsl_rng_uniform (r);
    d.xx[i] = xmax * (u-0.5);
  }
  
  for(i=0; i < n; i++){
    d.sigma[i]= gsl_ran_gaussian (r, 0.1);
    d.y[i] = c1* pow(d.xx[i],2.0) +  c2 * d.xx[i] + c3;
    d.y[i]+=alpha *  gsl_ran_gaussian (r, 1.0);
  }
  
  inpf=fopen("input.dat","w");
  for(i=0; i < n; i++)
    fprintf(inpf,"%2.6f %2.6f\n",d.xx[i],d.y[i]);
  
  f.f = &func_f; // the function
  f.df = &func_df; // the jacobian 
  f.fdf = &func_fdf; // a container for both 
  f.n = n; // # of fitting points
  f.p = p; // # of parameters = 3
  f.params = &d; // data structure 
  
  T = gsl_multifit_fdfsolver_lmsder; // the solver 
  s = gsl_multifit_fdfsolver_alloc (T,n,p);
  gsl_multifit_fdfsolver_set (s, &f, &x.vector);

  fprintf (stderr,"s is a '%s' solver\n",  gsl_multifit_fdfsolver_name (s));
  
  print_state (iter, s);
  
  // this is the main iteration loop 
  do
    {
      iter++;
      status = gsl_multifit_fdfsolver_iterate (s);
      
      fprintf (stderr,"status = %s\n", gsl_strerror (status));
      
      print_state (iter, s);
      
      if (status)
        break;
      
      // this is stopping condition i.e., if relerror < e-4 or abserror < e-4 stop
      status = gsl_multifit_test_delta (s->dx, s->x,
                                        1e-4, 1e-4);
    }
  
  while (status == GSL_CONTINUE && iter < 500);
  
  gsl_multifit_covar (s->J, 0.0, covar);
  
#define FIT(i) gsl_vector_get(s->x, i)
#define ERR(i) sqrt(gsl_matrix_get(covar,i,i))
  
  {
    double chi = gsl_blas_dnrm2(s->f); 
  // this is sqrt[ sum_{i=1,n} pow((y_i-y(x_i))/sigma(i),2)=chi]
    double dof = n - p;
    double c = GSL_MAX_DBL(1, chi / sqrt(dof));
    
    fprintf(stderr,"chisq/dof = %g\n",  pow(chi, 2.0) / dof);
    
    for(i=0; i < p; i++){
      fprintf(stderr,"%2.6f\n",FIT(i));
    }
  }
  
  fprintf (stderr,"status = %s\n", gsl_strerror (status));
  
  gsl_multifit_fdfsolver_free (s);
  gsl_matrix_free (covar);
  gsl_rng_free (r);
  return 0;
  
}

void print_state (size_t iter, gsl_multifit_fdfsolver * s)
{
  int i,p=3;
  printf("\n iter = %d  ",(int) iter);
  
  for(i=0; i < p; i++)
    printf("  %2.6f  ",gsl_vector_get (s->x, i));
   printf("  %2.6f\n", gsl_blas_dnrm2 (s->f));
  
}


