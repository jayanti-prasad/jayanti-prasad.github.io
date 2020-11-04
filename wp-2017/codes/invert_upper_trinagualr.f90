!-------------------------------------------------------------------
!-  This program shows how to compute the inverse of an upper trinagular 
!   matrix using LAPACK/BLAS
!-  The file which contains the matrix has to be passed at the run time.
!
!               Jayanti Prasad, Sept 20, 2011
!               Comments & Feedback: prasad.jayanti@gmail.com   
!------------------------------------------------------------------

program inverse 
  implicit none 
  integer :: n , LDA
  double precision, dimension(:,:),allocatable :: A, B,C,D 
  integer :: i, j,k,INFO,numarg  
  character (len=240)inputfile,str
  CALL GETARG(1, STR)
  read (STR,'(A)')inputfile
  
  numarg = iargc ( )
  
  if (numarg .lt. 1) then
     write(*,*)"ERROR ! Plase give the input file prefix"
     write(*,*)"./invert_upper_trinagualr  <input file> "
     stop
  end if
  
  open(11,file=trim(inputfile))
  read(11,*)N,LDA
  
  allocate(A(N,N))
  allocate(B(N,N))
  allocate(C(N,N))
  
  do i = 1, n 
     read(11,*) (A(i,j),j=1,n)
  end do
  
  B = A
  
  call DTRTRI('U','N', N, A, LDA, INFO )
  
  write(*,*)"-----------------A-------------------------------------------------"
  do i = 1, n 
     write(*,'(6(F12.6))')(B(i,j),j=1,n) 
  end do
  
  write(*,*)"-----------------A^-1----------------------------------------------"
  do i = 1, n
     write(*,'(6(F12.6))')(A(i,j),j=1,n)
  end do
  
  C = MATMUL(A,B) 
  
  write(*,*)"-----------------A X A^-1------------------------------------------"
  do i = 1, n
     write(*,'(6(F12.6))')(C(i,j),j=1,n)
  end do
  
end program inverse


! compile 
! gfortran invert_upper_trinagualr.f90  /data2/jayanti/software/lapack-3.2.2/lapack_LINUX.a\
!  /data2/jayanti/software/lapack-3.2.2/blas_LINUX.a
