#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

double timediff(struct timeval t1, struct timeval t2){
  double dt;
  dt = (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000.0;
  return(dt);
}

