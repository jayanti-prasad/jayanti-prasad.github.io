CC=gcc
FFTW3=/data1/software/fftw3
all : create_data example_dft_1d  example_dft_2d example_dft_3d   

create_data: create_data.c
	$(CC) create_data.c -o create_data -lm 

example_dft_1d: example_dft_1d.c  modes.c
	$(CC)  modes.c example_dft_1d.c -o example_dft_1d -I$(FFTW3)/include -L$(FFTW3)/lib -lfftw3 -lm  

example_dft_2d: example_dft_2d.c  modes.c
	$(CC)  modes.c example_dft_2d.c -o example_dft_2d -I$(FFTW3)/include -L$(FFTW3)/lib -lfftw3 -lm 
example_dft_3d: example_dft_3d.c  modes.c
	$(CC)  modes.c example_dft_3d.c -o example_dft_3d -I$(FFTW3)/include -L$(FFTW3)/lib -lfftw3 -lm -fopenmp -lfftw3_omp 
clean:
	rm -rf *.o *.out *.err *~  example_dft_1d  example_dft_2d example_dft_3d create_data  
