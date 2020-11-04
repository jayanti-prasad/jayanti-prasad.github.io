CC=gcc
FLAG=-fopenmp 

all : compute_pi_omp  hello_world_omp  prime_number_omp  scalar_product_omp nbody_kernal_omp\
	first_private_omp last_private_omp  critical_omp barrier_omp schedule_omp  

compute_pi_omp:
	$(CC) $(FLAG) compute_pi_omp.c -o compute_pi_omp  -lm
hello_world_omp:
	$(CC) $(FLAG) hello_world_omp.c -o hello_world_omp -lm 
prime_number_omp:
	$(CC) $(FLAG) prime_number_omp.c -o prime_number_omp -lm 
scalar_product_omp:
	$(CC) $(FLAG) scalar_product_omp.c -o scalar_product_omp -lm 
nbody_kernal_omp:
	$(CC) $(FLAG)  time.c nbody_kernal_omp.c -o nbody_kernal_omp -lm 
first_private_omp:
	$(CC) $(FLAG) first_private_omp.c -o first_private  -lm
last_private_omp:
	$(CC) $(FLAG)  last_private_omp.c -o last_private -lm 
critical_omp:
	$(CC) $(FLAG)  critical_omp.c -o  critical_omp -lm 
barrier_omp:
	$(CC) $(FLAG) barrier_omp.c -o barrier_omp 
schedule_omp:
	$(CC) $(FLAG) schedule_omp.c -o schedule_omp 
clean:
	rm -rf *.o *~ compute_pi_omp  hello_world_omp  prime_number_omp\
  scalar_product_omp nbody_kernal_omp *.dat *~ first_private last_private\
 *.out *.dat  barrier_omp  critical_omp schedule_omp

