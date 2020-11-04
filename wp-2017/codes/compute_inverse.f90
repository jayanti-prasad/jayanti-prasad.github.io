!-----------------------------------------------------------------
!  This program compute the inverse of a general square matrix 
!  using BLAS/LAPACK.
!  The matrix has to be given from the input file which should 
!  have the first line the # of rows followd by the matrix entries
!  example of the inpute file
!  3
!  1.0 2.0 4.0
!  4.9 8.9 1.0
!  3.0 1.9 9.0 
!                           Jayanti Prasad, Sept 20, 2011
!          Comments & Feedback : prasad.jayanti@gmail.com          
!---------------------------------------------------------------
program inverse 
  implicit none 
  double precision, dimension(:,:),allocatable  :: A, B,C 
  integer, dimension(:), allocatable  :: IPIV
  double precision, dimension(:),allocatable ::  WORK
  integer :: i,j,ndim,INFO,LDA,LWORK,N,numarg  
  character (len=240)inputfile,str 
  
  numarg = iargc ( )
  
  if (numarg .lt. 1) then
     write(*,*)"ERROR ! Plase give the input file prefix"
     write(*,*)"./compute_inverse <input file>"
     stop
  end if
  
  CALL GETARG(1, STR)
  read (STR,'(A)')inputfile 
  
  open(11,file=inputfile)
  read(11,*)ndim 
  LDA=ndim
  LWORK=ndim
  N= ndim
  allocate(A(ndim,ndim))
  allocate(B(ndim,ndim))
  allocate(C(ndim,ndim))
  
  do i =  1, ndim 
     read(11,*)(A(i,j),j=1,ndim)
  end do
  close(11)
  
  ! Copy A into B for inverse 
  B=A
  
  allocate(IPIV(ndim))
  allocate(WORK(ndim))
  
  call  DGETRF(N, N, B, LDA, IPIV, INFO)
  call  DGETRI(N, B, LDA, IPIV, WORK, LWORK, INFO )
  
  write(*,*)"-----------------A------------------------------------------------"
  do i = 1, n 
     write(*,'(6(E12.4))')(A(i,j),j=1,n) 
  end do
  
  write(*,*)"-----------------A^-1 ---------------------------------------------"
  do i = 1, n
     write(*,'(6(E12.4))')(B(i,j),j=1,n)
  end do
  
  C = MATMUL(A,B) 
  
  write(*,*)"checking---" 
  write(*,*)"----------------A^-1 X A -------------------------------------------"
  do i = 1, n
     write(*,'(6(F12.4))')(C(i,j),j=1,n)
  end do
  
  write(*,'(6(F12.6))')(sqrt(B(I,i)),i=1,n) 
  
end program inverse
