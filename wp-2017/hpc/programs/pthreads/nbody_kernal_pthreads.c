/*-----------------------------------------------
  PTHREAD : HELLO WORLD 1
  
  
  * The main program asked threads to print 'Hello World'
  with their thread id.
  
  * Note that here nothing is returned from the subprogram 
  which every thread executes.
  
  [Comments & Suggestion : Jayanti Prasad 
  prasad.jayanti@gmail.com 
  http://www.iucaa.ernet.in/~jayanti/]

  Sun Jan 29 10:10:37 IST 2012
  
  --------------------------------------------------*/
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>

#define NLARGE 1000000 
#define MG  1000.0 
#define EPS 0.001
#define NDIM 3
#define BOX_SIZE 100.0 

double urand();
double timediff(struct timeval , struct timeval );

double *r, *f;
int npart,num_threads;

void *tfunc(void *arg){
  long    my_id = (long) arg;
  int i,j,l,ndim=NDIM,chunck_size;
  float dr[ndim],dr2; 


  chunck_size = npart/num_threads; 
 
  for(i=my_id*chunck_size; i < (my_id+1)*chunck_size; i++){
    for(j=0; j < npart; j++){
      if (i !=j){   
        dr2 = (double) (EPS*EPS);
        for(l=0; l < ndim; l++){
          dr[l] = r[l+ndim*j]-r[l+ndim*i]; 
          dr2   += dr[l] * dr[l]; 
        }
        for(l=0; l < ndim; l++){
          f[l+ndim*i] += MG * dr[l]/(dr2*sqrt(dr2)); 
        }
      }
    }
  }
}

int main(int argc, char *argv[]){
  int n,j,ndim=NDIM;
  long i;
  pthread_t *t;
  FILE *fp1, *fp2;
  struct timeval  t1,t2, t3, t4;
  struct timezone tzp;
 
   gettimeofday (&t1, &tzp);
  
   if(argc < 2){
    fprintf(stderr,"./hello_world <# threads>\n");
    return(-1);
  }
 
  num_threads = atoi(argv[1]);
  n = atoi(argv[2]);
  npart  =  n * n * n;
 
  t = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
  r = (double *)malloc(npart*ndim*sizeof(double));
  f = (double *)malloc(npart*ndim*sizeof(double));
 
  
  for(i=0; i < npart; i++){
    for(j=0; j < ndim; j++){
      r[j+ndim*i] = (double) BOX_SIZE * urand();
      f[j+ndim*i] = 0.0;
    }
  }
 
 gettimeofday (&t2, &tzp);
 
  for(i=0; i < num_threads; i++){
    pthread_create(&t[i],NULL,tfunc,(void *)i);
  }
  
  for(i=0; i < num_threads; i++){
    pthread_join(t[i],NULL) ;
  }

  gettimeofday (&t3, &tzp); 
  
  fp1 = fopen("pos.dat","w"); 
  fp2 = fopen("force.dat","w"); 
  for(i=0; i < npart; i++){
    fprintf(fp1,"%.6f %.6f %.6f\n",r[0+ndim*i],r[1+ndim*i],r[2+ndim*i]); 
    fprintf(fp2,"%.6f %.6f %.6f\n",f[0+ndim*i],f[1+ndim*i],f[2+ndim*i]); 
  }
  fclose(fp1);
  fclose(fp2);
  
  gettimeofday (&t4, &tzp); 
  
  printf("time spent on serial  section = %.6f sec \n",timediff(t1,t2)+timediff(t3,t4)); 
  printf("time spent on paralle section = %.6f sec \n",timediff(t2,t3)); 


 
 return(0);
}

double urand(){
  double x;
  int ir;

  ir = rand() % NLARGE;
  x = (double) ir/NLARGE;
  return(x);

}

double timediff(struct timeval t1, struct timeval t2){
  double dt;
  dt = (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000.0;
  return(dt);
}
          
