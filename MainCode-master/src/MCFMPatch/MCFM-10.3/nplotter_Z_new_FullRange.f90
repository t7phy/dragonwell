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

          histos(1) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y1')

          histos(2) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y2')

          histos(3) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y3')

          histos(4) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y4')

          histos(5) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y5')

          histos(6) = plot_setup_custom([0.d0, 2.d0, 4.d0, 6.d0, 8.d0, 10.d0, &
                                       13.d0, 16.d0, 20.d0, 25.d0, 30.d0, &
                                       37.d0, 45.d0, 55.d0, 65.d0, 75.d0, &
                                       85.d0, 105.d0, 150.d0, 200.d0, 900.d0],&
                                       'ATLAS8TeV_pT_Y6')

          histos(7) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.5, 25.0, &
                                       27.5, 30.0, 33.0, 36.0, 39.0, 42.0, &
                                       45.0, 48.0, 51.0, 54.0, 57.0, 61.0, &
                                       65.0, 70.0, 75.0, 80.0, 85.0, 95.0, &
                                       105.0, 125.0, 150.0, 175.0, 200.0, &
                                       250.0, 300.0, 350.0, 400.0, 470.0, &
                                       550.0, 650.0, 900.0], &
                                       'ATLAS8TeV_pT')

          histos(8) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.5, 25.0, &
                                       27.5, 30.0, 33.0, 36.0, 39.0, 42.0, &
                                       45.0, 48.0, 51.0, 54.0, 57.0, 61.0, &
                                       65.0, 70.0, 75.0, 80.0, 85.0, 95.0, &
                                       105.0, 125.0, 150.0, 175.0, 200.0, &
                                       250.0, 300.0, 350.0, 400.0, 470.0, &
                                       550.0, 650.0, 900.0], &
                                       'ATLAS13TeV_pT')

          histos(9) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, &
                                       14.0, 16.0, 18.0, 22.0, 26.0, 30.0, &
                                       34.0, 38.0, 42.0, 46.0, 50.0, 54.0, &
                                       60.0, 70.0, 80.0, 100.0, 150.0, 200.0, &
                                       300.0, 800.0], &
                                       'ATLAS7TeV_pT_Y1')

          histos(10) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0,&
                                       14.0, 16.0, 18.0, 22.0, 26.0, 30.0, &
                                       34.0, 38.0, 42.0, 46.0, 50.0, 54.0, &
                                       60.0, 70.0, 80.0, 100.0, 150.0, 200.0, &
                                       300.0, 800.0], &
                                       'ATLAS7TeV_pT_Y2')

          histos(11) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0,&
                                       14.0, 16.0, 18.0, 22.0, 26.0, 30.0, &
                                       34.0, 38.0, 42.0, 46.0, 50.0, 54.0, &
                                       60.0, 70.0, 80.0, 100.0, 150.0, 200.0, &
                                       300.0, 800.0], &
                                       'ATLAS7TeV_pT_Y3')

          histos(12) = plot_setup_custom([0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0,&
                                       14.0, 16.0, 18.0, 22.0, 26.0, 30.0, &
                                       34.0, 38.0, 42.0, 46.0, 50.0, 54.0, &
                                       60.0, 70.0, 80.0, 100.0, 150.0, 200.0, &
                                       300.0, 800.0], &
                                       'ATLAS7TeV_pT')

          histos(13) = plot_setup_custom([0.0, 2.5, 5.0, 7.5, 10.0, 12.5, &
                                     15.0, 17.5, 20.0, 30.0, 40.0, 50.0, &
                                     70.0, 90.0, 110.0, 150.0, 190.0, &
                                     250.0, 600.0], &
                                     'CMS7TeV_pT')

          histos(14) = plot_setup_custom([0.0, 2.5, 5.0, 7.5, 10.0, 12.5, &
                                     15.0, 17.5, 20.0, 30.0, 40.0, 50.0, &
                                     70.0, 90.0, 110.0, 150.0, 190.0, &
                                     250.0, 600.0], &
                                     'CMS8TeV_pT')

          histos(15) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 1500.0], &
                                       'CMS13TeV_pT_Y1')

          histos(16) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 1500.0], &
                                       'CMS13TeV_pT_Y2')

          histos(17) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 1500.0], &
                                       'CMS13TeV_pT_Y3')

          histos(18) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 1500.0], &
                                       'CMS13TeV_pT_Y4')

          histos(19) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 1500.0], &
                                       'CMS13TeV_pT_Y5')

          histos(20) = plot_setup_custom([1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, &
                                       8.0, 9.0, 10.0, 11.0, 12.0, 13.0, &
                                       14.0, 16.0, 18.0, 20.0, 22.0, 25.0, &
                                       28.0, 32.0, 37.0, 43.0, 52.0, 65.0, &
                                       85.0, 120.0, 160.0, 190.0, 220.0, &
                                       250.0, 300.0, 400.0, 500.0, 800.0, &
                                       1500.0], &
                                       'CMS13TeV_pT')

          histos(21) = plot_setup_custom([0.0, 2.2, 3.4, 4.6, 5.8, 7.2, 8.7, &
                                       10.5, 12.8, 15.4, 19.0, 24.5, 34.0, &
                                       63.0, 270.0], &
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
          real(dp) :: yraptwo
          real(dp) :: pt34, trans04, trans06, y34
          real(dp) :: phistar, phiacop, costhetastar, delphi34

          real(dp) :: isY1, isY2, isY3, isY4, isY5, isY6
          real(dp) :: isATL7Y1, isATL7Y2, isATL7Y3
          real(dp) :: isCMSY1, isCMSY2, isCMSY3, isCMSY4, isCMSY5
          real(dp) :: isLHCb, isYmax

          pt34 = pttwo(3,4,p)
          y34=yraptwo(3,4,p)

          delphi34 = delphi(p(3,:),p(4,:))
          phiacop = 2._dp*atan(sqrt((1._dp+cos(delphi34))/(1._dp-cos(delphi34))))
          costhetastar = tanh((etarap(3,p)-etarap(4,p))/2._dp)
          phistar = tan(phiacop/2._dp)*sin(acos(costhetastar))

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

          isY1 = 0.0d0
          isY2 = 0.0d0
          isY3 = 0.0d0
          isY4 = 0.0d0
          isY5 = 0.0d0
          isY6 = 0.0d0
          isATL7Y1 = 0.0d0
          isATL7Y2 = 0.0d0
          isATL7Y3 = 0.0d0
          isCMSY1 = 0.0d0
          isCMSY2 = 0.0d0
          isCMSY3 = 0.0d0
          isCMSY4 = 0.0d0
          isCMSY5 = 0.0d0
          isYmax = 0.0d0

          if(abs(y34) < 0.4) then
            isY1 = 1.0d0
          endif
          if(abs(y34) < 0.8 .and. abs(y34) > 0.4) then
            isY2 = 1.0d0
          endif
          if(abs(y34) < 1.2 .and. abs(y34) > 0.8) then
            isY3 = 1.0d0
          endif
          if(abs(y34) < 1.6 .and. abs(y34) > 1.2) then
            isY4 = 1.0d0
          endif
          if(abs(y34) < 2.0 .and. abs(y34) > 1.6) then
            isY5 = 1.0d0
          endif
          if(abs(y34) < 2.4 .and. abs(y34) > 2.0) then
            isY6 = 1.0d0
          endif
          if(abs(y34) < 1.0) then
            isATL7Y1 = 1.0d0
          endif
          if(abs(y34) < 2.0 .and. abs(y34) > 1.0) then
            isATL7Y2 = 1.0d0
          endif
          if(abs(y34) < 2.4 .and. abs(y34) > 2.0) then
            isATL7Y3 = 1.0d0
          endif
          if(abs(y34) < 0.4) then
            isCMSY1 = 1.0d0
          endif
          if(abs(y34) < 0.8 .and. abs(y34) > 0.4) then
            isCMSY2 = 1.0d0
          endif
          if(abs(y34) < 1.2 .and. abs(y34) > 0.8) then
            isCMSY3 = 1.0d0
          endif
          if(abs(y34) < 1.6 .and. abs(y34) > 1.2) then
            isCMSY4 = 1.0d0
          endif
          if(abs(y34) < 2.4 .and. abs(y34) > 1.6) then
            isCMSY5 = 1.0d0
          endif
          if(abs(y34) < 2.4) then
            isYmax = 1.0d0
          endif

          ids = histos
          vals = [pt34, pt34, pt34, pt34, pt34, pt34, pt34, &
                  pt34, pt34, pt34, pt34, pt34, pt34, pt34, &
                  pt34, pt34, pt34, pt34, pt34, pt34, pt34]

          wts  = [wt*isY1, wt*isY2, wt*isY3, wt*isY4, wt*isY5, wt*isY6, &
                  wt*isYmax, wt, wt*isATL7Y1, wt*isATL7Y2, wt*isATL7Y3, &
                  wt*isYmax, &
                  wt, wt, wt*isCMSY1, wt*isCMSY2, wt*isCMSY3, wt*isCMSY4, &
                  wt*isCMSY5, wt*isYmax, wt]

      end subroutine

end module
