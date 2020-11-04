#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int modes(int n, float f[]){
 int i ;

// fc = f_nyq = 1/ 2 Delta ; delta = (xmax-xmin)/(n-1) 
// so f_nyq =1/ (2*(xmax-xmin)/(n-1)) = (n-1)/2(xmax-xmin) 
// frequnecy spectrum : [-fc,fc] :  2f_c *(i/n) where i = -n/2 to n/2
  

  for(i=0; i < n/2; i++)
   f[i] = (float )i/n;

  for(i=n/2+1; i < n; i++)
   f[i] = -  (float )(n-i)/n;

   f[n/2] = 1.0/2;
 
   return(0); 
 }
