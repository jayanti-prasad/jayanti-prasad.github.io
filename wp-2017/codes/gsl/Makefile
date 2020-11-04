CC=gcc
GSL=/data/software/gsl
PGPLOT= -lpgplot -lcpgplot -lm

all : uran gran histogram plothist 

uran:
	$(CC) uran.c -o uran -I$(GSL)/include -L$(GSL)/lib -lgsl  -lgslcblas  

gran:
	$(CC) gran.c -o gran -I$(GSL)/include -L$(GSL)/lib -lgsl  -lgslcblas 

histogram:
	$(CC) histogram.c -o histogram -I$(GSL)/include -L$(GSL)/lib -lgsl  -lgslcblas

plothist:
	$(CC) plothist.c -o plothist $(PGPLOT) 

clean:
	rm -rf *~ uran gran histogram plothist 




