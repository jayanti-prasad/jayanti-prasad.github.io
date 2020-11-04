CC=gcc

all:  compute_pi_pthreads hello_world1_pthreads hello_world2_pthreads\
	 mutex1_pthreads nbody_kernal_pthreads return_pthreads\
	 scalar_prod_pthreads summation1_pthreads summation2_pthreads \
	 mutex2_pthreads create_pthreads create_fork stack_pthreads  

compute_pi_pthreads:
	$(CC) compute_pi_pthreads.c -o compute_pi_pthreads -lpthread -lm
hello_world1_pthreads:
	$(CC) hello_world1_pthreads.c -o hello_world1_pthreads -lpthread -lm
hello_world2_pthreads:
	$(CC) hello_world2_pthreads.c -o hello_world2_pthreads -lpthread -lm
mutex1_pthreads:
	$(CC) mutex1_pthreads.c -o mutex1_pthreads -lpthread -lm
mutex2_pthreads:
	$(CC) mutex2_pthreads.c -o mutex2_pthreads -lpthread -lm
nbody_kernal_pthreads:
	$(CC) nbody_kernal_pthreads.c -o nbody_kernal_pthreads -lpthread -lm
return_pthreads:
	$(CC) return_pthreads.c -o return_pthreads -lpthread -lm
scalar_prod_pthreads:
	$(CC) scalar_prod_pthreads.c  -o scalar_prod_pthreads  -lpthread -lm
summation1_pthreads:
	$(CC) summation1_pthreads.c -o summation1_pthreads -lpthread -lm
summation2_pthreads:
	$(CC) summation2_pthreads.c -o summation2_pthreads -lpthread -lm
create_pthreads:
	$(CC) create_pthreads.c -o create_pthreads  -lpthread -lm
create_fork:
	$(CC) create_fork.c -o create_fork -lpthread -lm
stack_pthreads:
	$(CC) stack_pthreads.c -o stack_pthreads -lpthread -lm
clean:  
	rm -rf *~ *.dat compute_pi_pthreads force_pp_pthreads  hello_world1_pthreads\
 	hello_world2_pthreads mutex1_pthreads nbody_kernal_pthreads\
  return_pthreads scalar_prod_pthreads summation1_pthreads summation2_pthreads mutex2_pthreads\
	create_pthreads create_fork stack_pthreads  mutex2_pthreads create_pthreads a.out  
