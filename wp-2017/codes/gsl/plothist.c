#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<cpgplot.h>

int main(int argc, char *argv[]){
  int i,n,ix,nbin;
  float *x,x1=1.0e8,x2=1.0e-8,y1,y2;
  FILE *inpf;
  int pflag =1;  

  if (argc < 3){
      fprintf(stderr,"./plothist <inputfile> <#bins> \n");
      fprintf(stderr," ./plothist vsr.dat 100 \n");
      return(-1); 
  }
  
  inpf = fopen(argv[1],"r"); 
  nbin = atoi(argv[2]);

  x = (float *)malloc(sizeof(float ));
  i =0;
  while(!feof(inpf)){
    fscanf(inpf,"%f\n",&x[i]);
   if (x[i]  < x1) 
      x1=x[i];
   if(x[i] >  x2)
     x2=x[i]; 
    i++;
    x = realloc(x,(i+1)*sizeof(float));
  }
  n = i; 
 
  cpgbeg(0,"?",1,1);
  cpgpap(10.0,0.8);
  cpgsci(2);  
  cpgsvp(0.0,1.0,0.0,1.0);
  cpgenv(x1,x2,0.0,5.0*(float)n/nbin,2,1);
  cpglab("", "","");
  cpgsci(3);
  cpghist(n,x,x1,x2,nbin,pflag);

  cpgend();

  return(0); 

}

