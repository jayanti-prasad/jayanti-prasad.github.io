#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<cpgplot.h>

int main(int argc, char *argv[]){
  int i,n,ix,nbin;
  float *x,x1,x2,y1,y2;
  FILE *inpf;
  int pflag =3;  

  if (argc < 6){
      fprintf(stderr,"./plothist <inputfile> <#bins> <xmin> <xmax> <ymin> <ymax> \n");
      fprintf(stderr," ./plothist  out.out  10 0.0 10.0 0.0 1000.0 \n");
      return(-1); 
  }
  
  inpf = fopen(argv[1],"r"); 
  nbin = atoi(argv[2]);
  x1 = atof(argv[3]);
  x2 = atof(argv[4]);
  y1 = atof(argv[5]);
  y2 = atof(argv[6]);

  x = (float *)malloc(sizeof(float ));
  i =0;
  while(!feof(inpf)){
    fscanf(inpf,"%f\n",&x[i]);
    i++;
    x = realloc(x,(i+1)*sizeof(float));
  }
  n = i; 
 
  cpgbeg(0,"?",1,1);
  cpgpap(10.0,0.8);
  cpgsci(2);  
  cpgsvp(0.0,1.0,0.0,1.0);
  cpgenv(x1,x2,y1,y2,2,1);
  cpglab("", "","");
  cpgsci(3);
  cpghist(n,x,x1,x2,nbin,pflag);

  cpgend();

  return(0); 

}

