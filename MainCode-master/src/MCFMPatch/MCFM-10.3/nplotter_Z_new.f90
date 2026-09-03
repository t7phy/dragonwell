!
!  SPDX-License-Identifier: GPL-3.0-or-later
!  Copyright (C) 2019-2022, respective authors of MCFM.
!
 
module nplotter_Z
      use types
      use MCFMPlotting
      use ResummationTransition, only: transition
      use qtResummation_params, only: transitionSwitch
      implicit none

      public :: setup, book
      private

      integer, save, allocatable :: histos(:)

      contains

      subroutine setup()
          use types
          use parseinput
          implicit none
          include 'mpicommon.f'

          include 'first.f'    
          if (first .and. rank == 0) then
            write(6,*) 'Using plotting routine nplotter_Z_new.f90'
            first=.false.
          endif
          allocate(histos(21))

          if (rank == 0) then
              write (*,*) "RESUMMATION: Using transition with switch ", transitionSwitch
          endif

          histos(1) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y1')

          histos(2) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y2')

          histos(3) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y3')

          histos(4) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y4')

          histos(5) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y5')

          histos(6) = plot_setup_custom([20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y6')

          histos(7) = plot_setup_custom([20.d0, 22.5d0, 25.d0, &
                                       27.5d0, 30.d0, 33.d0, 36.d0, 39.d0, 42.d0, &
                                       45.d0, 48.d0, 51.d0, 54.d0, 57.d0, 61.d0, &
                                       65.d0, 70.d0, 75.d0, 80.d0, 85.d0, 95.d0, &
                                       105.d0, 125.d0, 150.d0, 175.d0, 200.d0, &
                                       250.d0, 300.d0, 350.d0, 400.d0, 470.d0, &
                                       550.d0, 650.d0, 900.d0], &
                                       'ATLAS8TeV_pT')

          histos(8) = plot_setup_custom([20.d0, 22.5d0, 25.d0, &
                                       27.5d0, 30.d0, 33.d0, 36.d0, 39.d0, 42.d0, &
                                       45.d0, 48.d0, 51.d0, 54.d0, 57.d0, 61.d0, &
                                       65.d0, 70.d0, 75.d0, 80.d0, 85.d0, 95.d0, &
                                       105.d0, 125.d0, 150.d0, 175.d0, 200.d0, &
                                       250.d0, 300.d0, 350.d0, 400.d0, 470.d0, &
                                       550.d0, 650.d0, 900.d0], &
                                       'ATLAS13TeV_pT')

          histos(9) = plot_setup_custom([22.d0, 26.d0, 30.d0, &
                                       34.d0, 38.d0, 42.d0, 46.d0, 50.d0, 54.d0, &
                                       60.d0, 70.d0, 80.d0, 100.d0, 150.d0, 200.d0, &
                                       300.d0, 800.d0], &
                                       'ATLAS7TeV_pT_Y1')

          histos(10) = plot_setup_custom([22.d0, 26.d0, 30.d0, &
                                       34.d0, 38.d0, 42.d0, 46.d0, 50.d0, 54.d0, &
                                       60.d0, 70.d0, 80.d0, 100.d0, 150.d0, 200.d0, &
                                       300.d0, 800.d0], &
                                       'ATLAS7TeV_pT_Y2')

          histos(11) = plot_setup_custom([22.d0, 26.d0, 30.d0, &
                                       34.d0, 38.d0, 42.d0, 46.d0, 50.d0, 54.d0, &
                                       60.d0, 70.d0, 80.d0, 100.d0, 150.d0, 200.d0, &
                                       300.d0, 800.d0], &
                                       'ATLAS7TeV_pT_Y3')

          histos(12) = plot_setup_custom([22.d0, 26.d0, 30.d0, &
                                       34.d0, 38.d0, 42.d0, 46.d0, 50.d0, 54.d0, &
                                       60.d0, 70.d0, 80.d0, 100.d0, 150.d0, 200.d0, &
                                       300.d0, 800.d0], &
                                       'ATLAS7TeV_pT')

          histos(13) = plot_setup_custom([20.d0, 30.d0, 40.d0, 50.d0, &
                                     70.d0, 90.d0, 110.d0, 150.d0, 190.d0, &
                                     250.d0, 600.d0], &
                                     'CMS7TeV_pT')

          histos(14) = plot_setup_custom([20.d0, 30.d0, 40.d0, 50.d0, &
                                     70.d0, 90.d0, 110.d0, 150.d0, 190.d0, &
                                     250.d0, 600.d0], &
                                     'CMS8TeV_pT')

          histos(15) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 1500.d0], &
                                       'CMS13TeV_pT_Y1')

          histos(16) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 1500.d0], &
                                       'CMS13TeV_pT_Y2')

          histos(17) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 1500.d0], &
                                       'CMS13TeV_pT_Y3')

          histos(18) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 1500.d0], &
                                       'CMS13TeV_pT_Y4')

          histos(19) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 1500.d0], &
                                       'CMS13TeV_pT_Y5')

          histos(20) = plot_setup_custom([20.d0, 22.d0, 25.d0, &
                                       28.d0, 32.d0, 37.d0, 43.d0, 52.d0, 65.d0, &
                                       85.d0, 120.d0, 160.d0, 190.d0, 220.d0, &
                                       250.d0, 300.d0, 400.d0, 500.d0, 800.d0, &
                                       1500.d0], &
                                       'CMS13TeV_pT')

          histos(21) = plot_setup_custom([19.d0, 24.5d0, 34.d0, &
                                       63.d0, 270.d0], &
                                       'LHCb13TeV_pT')



!          histos(1) = plot_setup_custom([0.0010d0,0.0013d0,0.0016d0,0.0020d0, &
!                0.0025d0,0.0032d0,0.0040d0,0.0050d0,0.0063d0,0.0079d0, &
!                0.0100d0,0.0126d0,0.0158d0,0.0200d0,0.0251d0,0.0316d0, &
!                0.0398d0,0.0501d0,0.0631d0,0.0794d0,0.1000d0,0.1259d0, &
!                0.1585d0,0.1995d0,0.2512d0,0.3162d0,0.3981d0,0.5012d0, &
!                0.6310d0,0.7943d0,1.0000d0,1.2589d0,1.5849d0,1.9953d0, &
!                2.5119d0,3.1623d0,3.9811d0,5.0119d0,6.3096d0,7.9433d0, &
!                10.0000d0,12.5893d0,15.8489d0,19.9526d0,25.1189d0, &
!                31.6228d0,39.8107d0,50.1187d0,63.0957d0,79.4328d0,100.0000d0], &
!                'pt34_fine_notrans')
!
!          histos(2) = plot_setup_custom([0d0,2d0,4d0,6d0,8d0, &
!              10d0,12d0,14d0,16d0,18d0,20d0,22.5d0,25d0,27.5d0,30d0, &
!              33d0,36d0,39d0,42d0,45d0,48d0,51d0,54d0,57d0,61d0,65d0, &
!              70d0,75d0,80d0,85d0,95d0,105d0,125d0,150d0,175d0,200d0, &
!              250d0,300d0,350d0,400d0,470d0,550d0,650d0,900d0],'pt34_big_trans04')
!          histos(3) = plot_setup_custom([0d0,0.004d0,0.008d0,0.012d0, &
!              0.016d0,0.02d0,0.024d0,0.029d0,0.034d0,0.039d0,0.045d0, &
!              0.051d0,0.057d0,0.064d0,0.072d0,0.081d0,0.091d0,0.102d0, &
!              0.114d0,0.128d0,0.145d0,0.165d0,0.189d0,0.219d0,0.258d0, &
!              0.312d0,0.391d0,0.524d0,0.695d0,0.918d0,1.153d0,1.496d0, &
!              1.947d0,2.522d0,3.277d0,5d0,10d0],'phistar_trans04')
!
!          histos(4) = plot_setup_custom([0d0,2d0,4d0,6d0,8d0, &
!              10d0,12d0,14d0,16d0,18d0,20d0,22.5d0,25d0,27.5d0,30d0, &
!              33d0,36d0,39d0,42d0,45d0,48d0,51d0,54d0,57d0,61d0,65d0, &
!              70d0,75d0,80d0,85d0,95d0,105d0,125d0,150d0,175d0,200d0, &
!              250d0,300d0,350d0,400d0,470d0,550d0,650d0,900d0],'pt34_big_trans06')
!          histos(5) = plot_setup_custom([0d0,0.004d0,0.008d0,0.012d0, &
!              0.016d0,0.02d0,0.024d0,0.029d0,0.034d0,0.039d0,0.045d0, &
!              0.051d0,0.057d0,0.064d0,0.072d0,0.081d0,0.091d0,0.102d0, &
!              0.114d0,0.128d0,0.145d0,0.165d0,0.189d0,0.219d0,0.258d0, &
!              0.312d0,0.391d0,0.524d0,0.695d0,0.918d0,1.153d0,1.496d0, &
!              1.947d0,2.522d0,3.277d0,5d0,10d0],'phistar_trans06')


      end subroutine

      subroutine book(p,wt,ids,vals,wts)
          use types
          use ResummationTransition
          use ieee_arithmetic
          implicit none
          include 'mxpart.f'
          include 'kpart.f'
          include 'taucut.f'! abovecut

          real(dp), intent(in) :: p(mxpart,4)
          real(dp), intent(in) :: wt

          integer, allocatable, intent(out) :: ids(:)
          real(dp), allocatable, intent(out) :: vals(:)
          real(dp), allocatable, intent(out) :: wts(:)

          real(dp) :: pttwo, twomass, delphi, etarap
          real(dp) :: yraptwo, pt
          real(dp) :: pt34, trans04, trans06, y34
          real(dp) :: phistar, phiacop, costhetastar, delphi34
          real(dp) :: pt3,pt4,eta3,eta4,m34

          real(dp) :: isY1, isY2, isY3, isY4, isY5, isY6
          real(dp) :: isATL8, isATL13
          real(dp) :: isATL7Y1, isATL7Y2, isATL7Y3, isATL7
          real(dp) :: isCMS7, isCMS8, isCMS13
          real(dp) :: isCMSY1, isCMSY2, isCMSY3, isCMSY4, isCMSY5
          real(dp) :: isLHCb
          integer isATLAS7TeV,isATLAS8TeV,isATLAS13TeV
          integer isCMS7TeV,isCMS8TeV,isCMS13TeV
          integer isLHCb13TeV

          pt34 = pttwo(3,4,p)
          y34=yraptwo(3,4,p)

          delphi34 = delphi(p(3,:),p(4,:))
          phiacop = 2._dp*atan(sqrt((1._dp+cos(delphi34))/(1._dp-cos(delphi34))))
          costhetastar = tanh((etarap(3,p)-etarap(4,p))/2._dp)
          phistar = tan(phiacop/2._dp)*sin(acos(costhetastar))

          m34=dsqrt((p(3,4)+p(4,4))**2-(p(3,1)+p(4,1))**2-(p(3,2)+p(4,2))**2-(p(3,3)+p(4,3))**2)

          pt3=pt(3,p)
          pt4=pt(4,p)
          eta3=etarap(3,p)
          eta4=etarap(4,p)

          ! the variable transitionSwitch is taken from the input file and can be used here
          ! instead of the hardcoded 0.4 and 0.6

          if (origKpart == kresummed) then
              if (abovecut .eqv. .false.) then
                  trans04 = transition((pt34/twomass(3,4,p))**2d0,0.001d0, 0.4d0 ,0.001d0)
                  trans06 = transition((pt34/twomass(3,4,p))**2d0,0.001d0, 0.6d0 ,0.001d0)
              else
                  ! fo piece without transition
                  trans04 = 1._dp
                  trans06 = 1._dp
              endif
          else
              trans04 = 1._dp
              trans06 = 1._dp
          endif

          if (ieee_is_nan(pt34)) then
              pt34 = -1._dp
          endif

          if (ieee_is_nan(phistar)) then
              phistar = -1._dp
          endif

          ! fill histograms: first without transition function
          ! then with 0.4 transition function, then with 0.6 transition function
          ! for estimating matching uncertainty

          if(pt3 > 20.0d0 .and. pt4 > 20.0d0 .and. abs(eta3) < 2.4d0 .and. abs(eta4) < 2.4d0 .and. m34 > 66.0d0 .and. m34 < 116.0d0 .and. abs(y34) < 2.4) then
            isATLAS7TeV = 1
          else
            isATLAS7TeV = 0
          endif

          if(pt3 > 20.0d0 .and. pt4 > 20.0d0 .and. abs(eta3) < 2.4d0 .and. abs(eta4) < 2.4d0 .and. m34 > 66.0d0 .and. m34 < 116.0d0 .and. abs(y34) < 2.4) then
            isATLAS8TeV = 1
          else
            isATLAS8TeV = 0
          endif

          if(pt3 > 27.0d0 .and. pt4 > 27.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 66.0d0 .and. m34 < 116.0d0) then
            isATLAS13TeV = 1
          else
            isATLAS13TeV = 0
          endif

          if(pt3 > 20.0d0 .and. pt4 > 20.0d0 .and. abs(eta3) < 2.1d0 .and. abs(eta4) < 2.1d0 .and. m34 > 60.0d0 .and. m34 < 120.0d0) then
            isCMS7TeV = 1
          else
            isCMS7TeV = 0
          endif

          if(pt3 > 20.0d0 .and. pt4 > 20.0d0 .and. abs(eta3) < 2.1d0 .and. abs(eta4) < 2.1d0 .and. m34 > 60.0d0 .and. m34 < 120.0d0) then
            isCMS8TeV = 1
          else
            isCMS8TeV = 0
          endif

          if(pt3 > 25.0d0 .and. pt4 > 25.0d0 .and. abs(eta3) < 2.4d0 .and. abs(eta4) < 2.4d0 .and. m34 > 76.1876d0 .and. m34 < 106.1876d0 .and. abs(y34) < 2.4) then
            isCMS13TeV = 1
          else
            isCMS13TeV = 0
          endif

          if(pt3 > 20.0d0 .and. pt4 > 20.0d0 .and. eta3 > 2.0d0 .and. eta3 < 4.5d0 .and. eta4 > 2.0d0 .and. eta4 < 4.5d0 .and. m34 > 60.0d0 .and. m34 < 120.0d0) then
            isLHCb13TeV = 1
          else
            isLHCb13TeV = 0
          endif


          isY1 = 0.0d0
          isY2 = 0.0d0
          isY3 = 0.0d0
          isY4 = 0.0d0
          isY5 = 0.0d0
          isY6 = 0.0d0
          isATL8 = 0.0d0
          isATL13 = 0.0d0
          isATL7Y1 = 0.0d0
          isATL7Y2 = 0.0d0
          isATL7Y3 = 0.0d0
          isATL7 = 0.0d0
          isCMS7 = 0.0d0
          isCMS8 = 0.0d0
          isCMSY1 = 0.0d0
          isCMSY2 = 0.0d0
          isCMSY3 = 0.0d0
          isCMSY4 = 0.0d0
          isCMSY5 = 0.0d0
          isCMS13 = 0.0d0
          isLHCb = 0.0d0

          if(abs(y34) < 0.4 .and. isATLAS8TeV .eq. 1) then
            isY1 = 1.0d0
          else
            isY1 = 0.0d0
          endif

          if(abs(y34) < 0.8 .and. abs(y34) > 0.4 .and. isATLAS8TeV .eq. 1) then
            isY2 = 1.0d0
          else
            isY2 = 0.0d0
          endif

          if(abs(y34) < 1.2 .and. abs(y34) > 0.8 .and. isATLAS8TeV .eq. 1) then
            isY3 = 1.0d0
          else
            isY3 = 0.0d0
          endif

          if(abs(y34) < 1.6 .and. abs(y34) > 1.2 .and. isATLAS8TeV .eq. 1) then
            isY4 = 1.0d0
          else
            isY4 = 0.0d0
          endif

          if(abs(y34) < 2.0 .and. abs(y34) > 1.6 .and. isATLAS8TeV .eq. 1) then
            isY5 = 1.0d0
          else
            isY5 = 0.0d0
          endif

          if(abs(y34) < 2.4 .and. abs(y34) > 2.0 .and. isATLAS8TeV .eq. 1) then
            isY6 = 1.0d0
          else
            isY6 = 0.0d0
          endif

          if(isATLAS8TeV .eq. 1) then
            isATL8 = 1.0d0
          else
            isATL8 = 0.0d0
          endif

          if(isATLAS13TeV .eq. 1) then
            isATL13 = 1.0d0
          else
            isATL13 = 0.0d0
          endif

          if(abs(y34) < 1.0 .and. isATLAS7TeV .eq. 1) then
            isATL7Y1 = 1.0d0
          else
            isATL7Y1 = 0.0d0
          endif

          if(abs(y34) < 2.0 .and. abs(y34) > 1.0 .and. isATLAS7TeV .eq. 1) then
            isATL7Y2 = 1.0d0
          else
            isATL7Y2 = 0.0d0
          endif

          if(abs(y34) < 2.4 .and. abs(y34) > 2.0 .and. isATLAS7TeV .eq. 1) then
            isATL7Y3 = 1.0d0
          else
            isATL7Y3 = 0.0d0
          endif

          if(isATLAS7TeV .eq. 1) then
            isATL7 = 1.0d0
          else
            isATL7 = 0.0d0
          endif

          if(isCMS7TeV .eq. 1) then
            isCMS7 = 1.0d0
          else
            isCMS7 = 0.0d0
          endif

          if(isCMS8TeV .eq. 1) then
            isCMS8 = 1.0d0
          else
            isCMS8 = 0.0d0
          endif

          if(abs(y34) < 0.4 .and. isCMS13TeV .eq. 1) then
            isCMSY1 = 1.0d0
          else
            isCMSY1 = 0.0d0
          endif

          if(abs(y34) < 0.8 .and. abs(y34) > 0.4 .and. isCMS13TeV .eq. 1) then
            isCMSY2 = 1.0d0
          else
            isCMSY2 = 0.0d0
          endif

          if(abs(y34) < 1.2 .and. abs(y34) > 0.8 .and. isCMS13TeV .eq. 1) then
            isCMSY3 = 1.0d0
          else
            isCMSY3 = 0.0d0
          endif

          if(abs(y34) < 1.6 .and. abs(y34) > 1.2 .and. isCMS13TeV .eq. 1) then
            isCMSY4 = 1.0d0
          else
            isCMSY4 = 0.0d0
          endif

          if(abs(y34) < 2.4 .and. abs(y34) > 1.6 .and. isCMS13TeV .eq. 1) then
            isCMSY5 = 1.0d0
          else
            isCMSY5 = 0.0d0
          endif

          if(isCMS13TeV .eq. 1) then
            isCMS13 = 1.0d0
          else
            isCMS13 = 0.0d0
          endif

          if(isLHCb13TeV .eq. 1) then
            isLHCb = 1.0d0
          else
            isLHCb = 0.0d0
          endif


          ids = histos
          vals = [pt34, pt34, pt34, pt34, pt34, pt34, pt34, &
                  pt34, pt34, pt34, pt34, pt34, pt34, pt34, &
                  pt34, pt34, pt34, pt34, pt34, pt34, pt34]

          wts  = [wt*isY1, wt*isY2, wt*isY3, wt*isY4, wt*isY5, wt*isY6, & !ATLAS8TeVY1,Y2,Y3,Y4,Y5,Y6
                  wt*isATL8, wt*isATL13, wt*isATL7Y1, wt*isATL7Y2, wt*isATL7Y3, wt*isATL7, & !ATLAS8TeV,ATLAS13TeV,ATLAS7TeVY1,Y2,Y3,ATLAS7TeV
                  wt*isCMS7, wt*isCMS8, wt*isCMSY1, wt*isCMSY2, wt*isCMSY3, wt*isCMSY4, & !CMS7TeV,CMS8TeV,CMS13TeVY1,Y2,Y3,Y4
                  wt*isCMSY5, wt*isCMS13, wt*isLHCb] !CMS13TeVY5,CMS13TeV,LHCb13TeV

      end subroutine

end module
