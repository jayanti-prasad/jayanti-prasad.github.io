#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<sys/time.h> 

#define NLARGE 1000000 
#define MG  1000.0 

double urand(); 

double timediff(struct timeval , struct timeval ); 

int main(int argc, char *argv[]){
 int numthreads, i, j, n, l,  npart, ndim=3;
 double *r, *f, dr2, drmod, dr[3], boxsize=100.0,eps2=1.0;  
 FILE *fp1, *fp2; 
 struct timeval  t1,t2, t3, t4;
 struct timezone tzp;

 gettimeofday (&t1, &tzp); 

 if (argc < 2){
  fprintf(stderr,"./a.out <num threads> <num points>\n");
  return(-1);
 } 

 numthreads = atoi(argv[1]);
 n = atoi(argv[2]);

 npart  =  n * n * n;

 omp_set_num_threads(numthreads);

 r = (double *)malloc(npart*ndim*sizeof(double));
 f = (double *)malloc(npart*ndim*sizeof(double));

 for(i=0; i < npart; i++){
    for(l=0; l < ndim; l++){
       r[l+ndim*i] = boxsize * urand();
       f[l+ndim*i] = 0.0;
   }
 }

 gettimeofday (&t2, &tzp); 

#pragma omp parallel for private (i,j,dr2,l) shared (npart,ndim,r,f)  schedule (static) 

for(i=0; i < npart; i++){
   for(j=0; j < npart; j++){
     if (i !=j){   
      dr2 = eps2;
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
