      subroutine integratehisto(N)
c--- Compute cumulative integral of histogram N and use it to
c--- replace current histogram N 
      implicit none
      include 'histo.f'
      integer N,j
      double precision xint
      
      xint=0d0
      
      do j=1,NBIN(N)

C_yfu
      if (isIrregBin(N) .eq. 0) then
        xint=xint+HIST(N,j)*HDEL(N)
      else if (isIrregBin(N) .eq. 1) then
        BinWidth=HistBinning(N,j+1)-HistBinning(N,j)
        xint=xint+HIST(N,j)*BinWidth
      endif
      HIST(N,j)=xint
      enddo
      
      j=index(title(N),'+INTEGRAL+')
      title(N)(j:j+9)='Cumulative'
      
      return
      end
      
      
