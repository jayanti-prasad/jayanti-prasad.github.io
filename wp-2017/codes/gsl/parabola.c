struct data {
  size_t n;
  double *xx;
  double *y;
  double *sigma;
};


int func_f(const gsl_vector *x,void *data,gsl_vector * f)
{
  size_t  n = ((struct data *)data)->n;
  double *xx = ((struct data *)data)->xx;
  double *y = ((struct data *)data)->y;
  double *sigma = ((struct data *) data)->sigma;
  size_t l;
  double Yi;

   double A = gsl_vector_get (x, 0);
   double B = gsl_vector_get (x, 1);
   double C = gsl_vector_get (x, 2);

  for(l=0; l < n; l++){
     Yi =  A*pow(xx[l],2.0) + B * xx[l] + C ;
     gsl_vector_set(f, l, (Yi - y[l])/sigma[l]);
   }
 return GSL_SUCCESS;
}

int  func_df (const gsl_vector *x,void *data,gsl_matrix * J)
{
  size_t n = ((struct data *)data)->n;
  double *sigma = ((struct data *) data)->sigma;
  double *xx = ((struct data *) data)->xx;
  double  t1,t2,t3;
  size_t  l;

  for (l = 0; l < n; l++)
    {
          t1 =  pow(xx[l],2.0) ;
          t2 =  xx[l] ;
          t3 =  1.0 ;
	  gsl_matrix_set (J, l,0,t1/sigma[l]);
	  gsl_matrix_set (J, l,1,t2/sigma[l]);
	  gsl_matrix_set (J, l,2,t3/sigma[l]);
    }
  return GSL_SUCCESS;
}

int func_fdf (const gsl_vector  *x, void *data, gsl_vector * f, gsl_matrix * J)
{
  func_f (x,data, f);
  func_df (x, data, J);
  
  return GSL_SUCCESS;
}



