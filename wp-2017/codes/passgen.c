#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>

char SML[]={'a','b','c','d','e','f','g','h','i','j','k','l',
	    'm','n','o','p','q','r','s','t','u','v','x','y','z', 'A','B',
	    'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
	    'S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7',
	    '8','9','%','#','$','%','&','@'}; 

int main(int argc, char *argv[]){
  int numchar;
  int numpasswd;
  int iseed; 
  int i,j,*iran,*itype,a,b,c,d;
  char *pwd; 
  char buf[100]; 
 
  if (argc < 3){
    fprintf(stdout,"./passgen <# characters in passwd> <# of passwords> <iseed> \n");
    return(-1);
  }
  
  numchar=atoi(argv[1]);
  numpasswd=atoi(argv[2]);
  iseed = atoi(argv[3]) + 1000; 

  iran=(int *)malloc(numchar*sizeof(int));
  itype=(int *)malloc(numchar*sizeof(int));
  pwd  =(char *)malloc(numpasswd*numchar*sizeof(char));
  
  i = 0;
  while (i < numpasswd){
     a = 0;
     b = 0;
     c = 0; 
     sprintf(buf,"");
     for(j=0; j < numchar; j++){
      iran[j] = (rand() % iseed) % 68;

      if(isalpha(SML[iran[j]]))
         a+=1;
      if(isdigit(SML[iran[j]]) )
         b+=1;
      if(!isalnum(SML[iran[j]]) )
        c+=1;  
      sprintf(buf,"%s%c",buf,SML[iran[j]]);
    }
    if( a > 0 & b > 0 & c > 0 & strlen(buf) >=numchar){
       printf("%s\n",buf); 
       i++;
    }
  }
  
  return(0); 
}
