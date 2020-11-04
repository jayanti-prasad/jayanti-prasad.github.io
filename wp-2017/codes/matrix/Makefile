CC=gcc  -Wall  
FC=gfortran 
GSL=/data2/jayanti/software/gsl
LAPACK=/data2/jayanti/software/lapack-3.2.2

all : compute_inverse  compute_eign compute_multi compute_det compute_svd 

compute_inverse:
	$(FC) compute_inverse.f90 -o compute_inverse $(LAPACK)/lapack_LINUX.a $(LAPACK)/blas_LINUX.a
compute_eign:
	$(CC) compute_eign.c -o compute_eign -I$(GSL)/include -L$(GSL)/lib  -lgsl  -lgslcblas  -lm
compute_multi:
	$(CC) compute_multi.c -o compute_multi -I$(GSL)/include -L$(GSL)/lib  -lgsl  -lgslcblas  -lm
compute_det:
	$(CC) compute_det.c -o compute_det -I$(GSL)/include -L$(GSL)/lib  -lgsl  -lgslcblas  -lm
compute_svd:
	$(CC) compute_svd.c -o compute_svd -I$(GSL)/include -L$(GSL)/lib  -lgsl  -lgslcblas  -lm


clean:
	rm -rf *~ compute_eign compute_inverse compute_multi compute_det linear_system  compute_det compute_svd
