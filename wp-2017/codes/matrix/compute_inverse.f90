program inverse 
 implicit none 
 double precision, dimension(:,:),allocatable  :: A, B,C 
 integer, dimension(:), allocatable  :: IPIV
 double precision, dimension(:),allocatable ::  WORK
 integer :: i,j,ndim,INFO,LDA,LWORK,N,numarg   
 character (len=240)inputfile,outputfile,str 

 numarg = iargc()

  if (numarg .lt. 2) then
     write(*,*)"ERROR ! Plase give use as follows"
     write(*,*)"./compute_inverse  <input file> <output file>"
     stop
  end if

  CALL GETARG(1, STR)
  read (STR,'(A)')inputfile 

  CALL GETARG(2, STR)
  read (STR,'(A)')outputfile 
      
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

  open(11,file=outputfile)
  write(11,*) n  
  do i = 1, n
     write(11,'(100(E12.4))')(B(i,j),j=1,n)
  end do
  close(11) 
  
  C = MATMUL(A,B) 
  
  write(*,*)"checking---" 
  write(*,*)"----------------A^-1 X A -------------------------------------------"
  do i = 1, n
     write(*,'(100(F12.4))')(C(i,j),j=1,n)
  end do

end program inverse 
