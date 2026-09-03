      subroutine nplotter_Zjets(p,wt,wt2,switch)
      implicit none
      include 'types.f'
c--- Variable passed in to this routine:
c
c---      p:  4-momenta of particles in the format p(i,4)
c---          with the particles numbered according to the input file
c---          and components labelled by (px,py,pz,E)
c
c---     wt:  weight of this event
c
c---    wt2:  weight^2 of this event
c
c--- switch:  an integer:: equal to 0 or 1, depending on the type of event
c---                0  --> lowest order, virtual or real radiation
c---                1  --> counterterm for real radiation
      
      include 'vegas_common.f'
      include 'constants.f'
      include 'nf.f'
      include 'mxpart.f'
      include 'histo.f'
      include 'jetlabel.f'
      include 'outputflags.f'
      include 'nproc.f'
      include 'energy.f'
      integer:: i5,i6,i7,nu
      real(dp):: p(mxpart,4),wt,wt2
      real(dp):: etarap,pt,
     & etaj1,ptj1,etaj2,ptj2,etaj3,ptj3,mjj,delr,getet,
     & rar,deleta,delfi,pt5,pt6,pt7,tmp5(4),tmp6(4),tmp7(4),oldpt(5:7),
     & sumeta,etastar,y34,eta34,pt34,y3,pt3,y4,pt4,yrap,yraptwo,
     & etaraptwo,pttwo
      real(dp):: y5,m34,r35
      real(dp):: L0, A0, A1, A2, A3, A4, A5, A6, A7, phi, sintheta
      real(dp):: costheta,p3(4),p4(4),p34(4),wt_ew
      real(dp):: sgn, p1(4), p2(4),boostedZ(4),boostedE(4),boostedP(4)
      real(dp):: CSAxis(3), yAxis(3), xAxis(3), dot3, angle, tmp(3)
      real(dp):: dot, cosphi, eminus, eplus, pminus, pplus, mt, zsign
      real(dp):: lambda(4,4), bE(4,1), lE(4,1), mt34
      integer:: switch,n,nplotmax,nnew
      integer tag
      common/nplotmax/nplotmax
      logical, save::first=.true.

C_yfu add for ppbar case
      integer:: ih1,ih2
      common/density/ih1,ih2

************************************************************************
*                                                                      *
*     INITIAL BOOKKEEPING                                              *
*                                                                      *
************************************************************************

c--- Initialize dummy values for all quantities that could be plotted
      ptj1=-1._dp
      ptj2=-1._dp
      ptj3=-1._dp
      etaj1=99._dp
      etaj2=99._dp
      etaj3=99._dp
      mjj=-1._dp
      delr=-1._dp
      deleta=-1._dp
      etastar=99._dp
      
      if (first) then
c--- Initialize histograms, without computing any quantities; instead
c--- set them to dummy values
        tag=tagbook
        goto 99
      else
c--- Add event in histograms
        tag=tagplot
      endif

************************************************************************
*                                                                      *
*     DEFINITIONS OF QUANTITIES TO PLOT                                *
*                                                                      *
************************************************************************

c--- Z rapidity and pseudorapidity
      y34=yraptwo(3,4,p)
      eta34=etaraptwo(3,4,p)
      pt34=pttwo(3,4,p)
      m34=sqrt(dot(p,3,4))

c--- lepton pt and rapidity
      y3=yrap(3,p)
      pt3=pt(3,p)
      y4=yrap(4,p)
      pt4=pt(4,p)

c--- BEGIN: order jets according to pt
      !pt5=getet(p(5,4),p(5,1),p(5,2),p(5,3))
      !if (jets > 1) pt6=getet(p(6,4),p(6,1),p(6,2),p(6,3))
      !if (jets > 2) pt7=getet(p(7,4),p(7,1),p(7,2),p(7,3))      
      !i5=5
      !i6=6
      !i7=7
      !oldpt(5)=pt5
      !if (jets > 1) oldpt(6)=pt6
      !if (jets > 2) oldpt(7)=pt7
c--- sort for 2 jets 
      !if (jets == 2) then          
      !  if (pt6 > pt5) then
      !    i5=6
      !    i6=5
      !  endif
      !endif
c--- sort for 3 jets 
      !if (jets == 3) then
      !  if ((pt5 > pt6) .and. (pt5 > pt7)) then
      !     i5=5
      !    if (pt6 > pt7) then
      !      i6=6
      !      i7=7
      !    else
      !      i6=7
      !      i7=6
      !    endif
      !  endif
      !  if ((pt6 > pt5) .and. (pt6 > pt7)) then
      !     i5=6
      !    if (pt5 > pt7) then
      !      i6=5
      !      i7=7
      !    else
      !      i6=7
      !      i7=5
      !    endif
      !  endif
      !  if ((pt7 > pt5) .and. (pt7 > pt6)) then
      !     i5=7
      !    if (pt5 > pt6) then
      !      i6=5
      !      i7=6
      !    else
      !      i6=6
      !      i7=5
      !    endif
      !  endif
      !endif
c--- perform exchange
      !do nu=1,4
      !     tmp5(nu)=p(i5,nu)
      !     tmp6(nu)=p(i6,nu)
      !     tmp7(nu)=p(i7,nu)
      !enddo
      !do nu=1,4
      !     p(5,nu)=tmp5(nu)
      !     p(6,nu)=tmp6(nu)
      !     p(7,nu)=tmp7(nu)
      !enddo
      !pt5=oldpt(i5)
      !if (jets > 1) pt6=oldpt(i6)
      !if (jets > 2) pt7=oldpt(i7)
c--- END: ordering

c--- Calculate quantities to plot
C      etaj1=etarap(5,p)
C      ptj1=pt(5,p)
C      if (jets >= 2) then
C        etaj2=etarap(6,p)
C        ptj2=pt(6,p)
C        deleta=abs(etaj1-etaj2)
C      endif
C      if (jets >= 3) then
C        etaj3=etarap(7,p)
C        ptj3=pt(7,p)
C      if     (abs(etaj1-etaj3) > 
C     &      max(abs(etaj1-etaj2),abs(etaj2-etaj3))) then
C          deleta=abs(etaj1-etaj3)
C        sumeta=etaj1+etaj3
C        etaj3=etaj2
C      elseif (abs(etaj2-etaj3) > 
C     &      max(abs(etaj1-etaj2),abs(etaj1-etaj3))) then
C          deleta=abs(etaj2-etaj3)
C        sumeta=etaj2+etaj3
C        etaj3=etaj1
C      else
C        deleta=abs(etaj1-etaj2)      
C        sumeta=etaj1+etaj2
C      endif
C      endif
C
C      rar=(p(5,1)*p(6,1)+p(5,2)*p(6,2))
C     & /sqrt((p(5,1)**2+p(5,2)**2)*(p(6,1)**2+p(6,2)**2))
C      if (rar<-1._dp) then 
C         delfi=pi
C      elseif (rar>1._dp) then 
C         delfi=0._dp
C      else
C         delfi=acos(rar)
C      endif
C      delr=sqrt(deleta**2+delfi**2)
C
C      if (jets > 1) then
C      mjj=sqrt((p(5,4)+p(6,4))**2-(p(5,1)+p(6,1))**2
C     &         -(p(5,2)+p(6,2))**2-(p(5,3)+p(6,3))**2)
C      endif
C            
C      if ((jets == 3) .and. (deleta >= 2._dp)) then
C        etastar=abs(etaj3-sumeta/2._dp)      
C      endif
        

************************************************************************
*                                                                      *
*     FILL HISTOGRAMS                                                  *
*                                                                      *
************************************************************************

c--- Call histogram routines
   99 continue

c--- Book and fill ntuple if that option is set, remembering to divide
c--- by # of iterations now that is handled at end for regular histograms
      if (creatent .eqv. .true.) then
        call bookfill(tag,p,wt/real(itmx,dp))  
      endif

c--- "n" will count the number of histograms
      n=nextnplot

c--- Syntax of "bookplot" routine is:
c
c---   call bookplot(n,tag,titlex,var,wt,wt2,xmin,xmax,dx,llplot)
c
c---        n:  internal number of histogram
c---      tag:  "book" to initialize histogram, "plot" to fill
c---   titlex:  title of histogram
c---      var:  value of quantity being plotted
c---       wt:  weight of this event (passed in)
c---      wt2:  weight of this event (passed in)
c---     xmin:  lowest value to bin
c---     xmax:  highest value to bin
c---       dx:  bin width
c---   llplot:  equal to "lin"/"log" for linear/log scale

!      call bookplot(n,tag,'Z rapidity',y34,wt,wt2,-5._dp,5._dp,0.4_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Z ps-rap',eta34,wt,wt2,-5._dp,5._dp,0.4_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'W pt',pt34,wt,wt2,0._dp,100._dp,2.5_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Z pt',pt34,wt,wt2,0._dp,1200._dp,50._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'y3',y3,wt,wt2,-5._dp,5._dp,0.4_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'pt3',pt3,wt,wt2,0._dp,200._dp,4._dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'y4',y4,wt,wt2,-5._dp,5._dp,0.4_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'pt4',pt4,wt,wt2,0._dp,200._dp,4._dp,'lin')
!      n=n+1
!
!      call bookplot(n,tag,'Jet 1 pt',ptj1,wt,wt2,
!     &              0._dp,12000._dp,500._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'Jet 1 pt low',ptj1,wt,wt2,
!     &              0._dp,2000._dp,50._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'Jet 1 pt high',ptj1,wt,wt2,
!     &              0._dp,40000._dp,1000._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'Jet 1 eta',etaj1,wt,wt2,
!     &              -5._dp,5._dp,0.2_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Jet 2 pt log',ptj2,wt,wt2,
!     &              20._dp,260._dp,5._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'Jet 2 pt lin',ptj2,wt,wt2,
!     &              20._dp,260._dp,5._dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Jet 2 eta',etaj2,wt,wt2,
!     &              -5._dp,5._dp,0.2_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Jet 3 pt log',ptj3,wt,wt2,
!     &              20._dp,170._dp,5._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'Jet 3 pt lin',ptj3,wt,wt2,
!     &              20._dp,170._dp,5._dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'Jet 3 eta',etaj3,wt,wt2,
!     &              -5._dp,5._dp,0.2_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'(jet 1,jet 2) invariant mass',mjj,wt,wt2,
!     &              0._dp,425._dp,5._dp,'log')
!      n=n+1
!      call bookplot(n,tag,'delr',delr,wt,wt2,
!     &              0.35_dp,4.85_dp,0.15_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'deleta',deleta,wt,wt2,
!     &              0._dp,4._dp,0.4_dp,'lin')
!      n=n+1
!      call bookplot(n,tag,'etastar',etastar,wt,wt2,
!     &              0._dp,3._dp,0.6_dp,'lin')
!      n=n+1
C--- Calculate angular functions
      p3(:) = p(3,:)
      p4(:) = p(4,:)
      p34(:) = p(3,:) + p(4,:)
      sgn = abs(p34(3))/p34(3)

C_yfu add for ppbar case
      if(ih2 .eq. -1) then
        sgn = 1.0
      endif

      p1(1) = 0
      p1(2) = 0
      p1(3) = sgn*sqrts/2.0
      p1(4) = sqrts/2.0
      p2(1) = 0
      p2(2) = 0
      p2(3) = -sgn*sqrts/2.0
      p2(4) = sqrts/2.0

      call boost2(m34,p34,p1,p1)
      call boost2(m34,p34,p2,p2)
      call boost2(m34,p34,p3,boostedE)

      call unitVec(p1(1:3), p1(1:3))
      call unitVec(p2(1:3), p2(1:3))
      tmp(1) = p1(1) - p2(1)
      tmp(2) = p1(2) - p2(2)
      tmp(3) = p1(3) - p2(3)
      call unitVec(tmp,CSAxis)

      call cross3(p2(1:3),p1(1:3),yAxis)
      call unitVec(yAxis,yAxis)
      call cross3(yAxis,CSAxis,xAxis)
      call unitVec(xAxis,xAxis)

      costheta = cos(angle(boostedE(1:3),CSAxis))
      sintheta = sqrt(1.0-costheta**2)
      phi = atan2(dot3(boostedE(1:3),yAxis),dot3(boostedE(1:3),xAxis))
      cosphi = cos(phi)

      A0 = (10.0/3.0*(1.0-3.0*costheta**2)+2.0/3.0)*wt 
      A1 = 10*sintheta*costheta*cosphi*wt
      A2 = 10*sintheta**2*(2*cosphi**2-1)*wt
      A3 = 4*sintheta*cosphi*wt
      A4 = 4*costheta*wt

      nnew = 1
      call dohist(nnew, 'A0YAL', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1

      call dohist(nnew, 'A1YAL', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1
  
      call dohist(nnew, 'A2YAL', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1
  
      call dohist(nnew, 'A3YAL', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1
    
      call dohist(nnew, 'A4YAL', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1
  
      call dohist(nnew, 'DSYAL', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
      nnew=nnew+1

C_yfu add for ppbar case
      if (ih2 .eq. -1) then

      if ((y34 > -0.4 .and. y34 < 0.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym04', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym04', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym04', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym04', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym04', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym04', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
          nnew = nnew+6
      endif

      if ((y34 < -0.4 .and. y34 > -0.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym08', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym08', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym08', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym08', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym08', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym08', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif

      if ((y34 < -0.8 .and. y34 > -1.2) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym12', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym12', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym12', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym12', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym12', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym12', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif

      if ((y34 < -1.2 .and. y34 > -1.6).or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym16', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym16', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym16', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym16', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym16', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym16', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -1.6 .and. y34 > -2.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym20', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym20', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym20', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym20', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym20', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym20', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -2.0 .and. y34 > -2.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym24', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym24', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym24', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym24', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym24', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym24', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -2.4 .and. y34 > -2.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym28', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym28', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym28', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym28', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym28', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym28', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -2.8 .and. y34 > -3.2) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym32', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym32', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym32', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym32', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym32', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym32', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -3.2 .and. y34 > -3.6) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym36', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym36', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym36', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym36', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym36', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym36', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -3.6 .and. y34 > -4.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym40', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym40', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym40', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym40', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym40', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym40', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -4.0 .and. y34 > -4.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym44', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym44', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym44', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym44', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym44', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym44', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -4.4 .and. y34 > -4.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym48', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym48', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym48', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym48', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym48', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym48', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < -4.8 .and. y34 > -5.2) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0ym52', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1ym52', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2ym52', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3ym52', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4ym52', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSym52', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if (y34 > 0.0 .and. y34 < 0.4 .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp04', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp04', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp04', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp04', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp04', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp04', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
          nnew = nnew+6
      endif

      if ((y34 < 0.8 .and. y34 > 0.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp08', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp08', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp08', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp08', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp08', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp08', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif

      if ((y34 < 1.2 .and. y34 > 0.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp12', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp12', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp12', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp12', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp12', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp12', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif

      if ((y34 < 1.6 .and. y34 > 1.2).or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp16', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp16', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp16', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp16', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp16', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp16', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 2.0 .and. y34 > 1.6) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp20', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp20', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp20', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp20', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp20', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp20', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 2.4 .and. y34 > 2.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp24', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp24', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp24', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp24', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp24', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp24', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 2.8 .and. y34 > 2.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp28', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp28', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp28', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp28', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp28', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp28', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 3.2 .and. y34 > 2.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp32', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp32', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp32', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp32', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp32', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp32', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 3.6 .and. y34 > 3.2) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp36', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp36', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp36', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp36', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp36', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp36', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 4.0 .and. y34 > 3.6) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp40', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp40', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp40', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp40', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp40', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp40', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 4.4 .and. y34 > 4.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp44', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp44', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp44', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp44', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp44', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp44', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 4.8 .and. y34 > 4.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp48', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp48', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp48', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp48', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp48', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp48', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((y34 < 5.2 .and. y34 > 4.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0yp52', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1yp52', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A2yp52', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A3yp52', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A4yp52', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'DSyp52', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

C pp case
      else

      if (abs(y34) < 0.4 .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y04', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y04', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y04', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y04', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y04', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy04', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
          nnew = nnew+6
      endif

      if ((abs(y34) < 0.8 .and. abs(y34) > 0.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y08', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y08', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y08', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y08', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y08', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy08', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif
      
      if ((abs(y34) < 1.2 .and. abs(y34) > 0.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y12', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y12', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y12', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y12', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y12', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy12', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
        nnew = nnew+6
      endif

      if ((abs(y34) < 1.6 .and. abs(y34) > 1.2).or. (tag == tagbook)) then
        call dohist(nnew, 'A0y16', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y16', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y16', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y16', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y16', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy16', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 2.0 .and. abs(y34) > 1.6) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y20', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y20', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y20', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y20', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y20', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy20', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 2.4 .and. abs(y34) > 2.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y24', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y24', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y24', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y24', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y24', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy24', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 2.8 .and. abs(y34) > 2.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y28', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y28', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y28', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y28', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y28', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy28', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif
  
      if ((abs(y34) < 3.2 .and. abs(y34) > 2.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y32', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y32', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y32', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y32', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y32', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy32', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif
  
      if ((abs(y34) < 3.6 .and. abs(y34) > 3.2) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y36', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y36', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y36', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y36', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y36', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy36', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 4.0 .and. abs(y34) > 3.6) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y40', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y40', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y40', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y40', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y40', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy40', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 4.4 .and. abs(y34) > 4.0) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y44', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y44', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y44', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y44', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y44', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy44', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 4.8 .and. abs(y34) > 4.4) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y48', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y48', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y48', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y48', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y48', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy48', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      if ((abs(y34) < 5.2 .and. abs(y34) > 4.8) .or. (tag == tagbook)) then
        call dohist(nnew, 'A0y52', pt34, A0, A0**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1

        call dohist(nnew, 'A1y52', pt34, A1, A1**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A2y52', pt34, A2, A2**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'A3y52', pt34, A3, A3**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
        
        call dohist(nnew, 'A4y52', pt34, A4, A4**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
    
        call dohist(nnew, 'DSy52', pt34, wt, wt**2,
     & (/  0._dp,   2.5_dp,   5._dp,   8._dp, 11.4_dp, 14.9_dp, 18.5_dp,
     &    22._dp,  25.5_dp,  29._dp, 36.4_dp, 40.4_dp, 44.9_dp, 50.2_dp,
     &   56.4_dp,  63.9_dp, 73.4_dp, 85.4_dp, 105._dp, 132._dp, 173._dp,
     &   253._dp,  600._dp/) )
        nnew=nnew+1
      else
      nnew = nnew+6
      endif

      endif

************************************************************************
*                                                                      *
*     FINAL BOOKKEEPING                                                *
*                                                                      *
************************************************************************

c--- We have over-counted the number of histograms by 1 at this point
      n=n-1

c--- Ensure the built-in maximum number of histograms is not exceeded    
      call checkmaxhisto(n)

c--- Set the maximum number of plots, on the first call
      if (first) then
        first=.false.
        nplotmax=n
      endif
      
      return 
      end
      
