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
          allocate(histos(12))

          if (rank == 0) then
              write (*,*) "RESUMMATION: Using transition with switch ", transitionSwitch
          endif

          histos(1) = plot_setup_custom([116.d0, 130.d0, 150.d0, &
                                       175.d0, 200.d0, 230.d0, 260.d0, 300.d0, &
                                       380.d0, 500.d0, 700.d0, 1000.d0, 1500.d0, &
                                       5000.d0], &
                                       'ATLAS13TeV_HighMassDY_1D_mass')

          histos(2) = plot_setup_custom([-1.d0, -0.8d0, -0.6d0, &
                                        -0.4d0, -0.2d0, 0.d0, 0.2d0, 0.4d0, &
                                         0.6d0,  0.8d0, 1.d0], &
                                       'ATLAS13TeV_HighMassDY_2D_CosTheta_mass1')

          histos(3) = plot_setup_custom([-1.d0, -0.8d0, -0.6d0, &
                                        -0.4d0, -0.2d0, 0.d0, 0.2d0, 0.4d0, &
                                         0.6d0,  0.8d0, 1.d0], &
                                       'ATLAS13TeV_HighMassDY_2D_CosTheta_mass2')

          histos(4) = plot_setup_custom([-1.d0, -0.8d0, -0.6d0, &
                                        -0.4d0, -0.2d0, 0.d0, 0.2d0, 0.4d0, &
                                         0.6d0,  0.8d0, 1.d0], &
                                       'ATLAS13TeV_HighMassDY_2D_CosTheta_mass3')

          histos(5) = plot_setup_custom([-1.d0, -0.8d0, -0.6d0, &
                                        -0.4d0, -0.2d0, 0.d0, 0.2d0, 0.4d0, &
                                         0.6d0,  0.8d0, 1.d0], &
                                       'ATLAS13TeV_HighMassDY_2D_CosTheta_mass4')

          histos(6) = plot_setup_custom([-1.d0, -0.75d0, -0.5d0, &
                                        -0.25d0, 0.d0, 0.25d0, 0.5d0, &
                                         0.75d0, 1.d0], &
                                       'ATLAS13TeV_HighMassDY_2D_CosTheta_mass5')

          histos(7) = plot_setup_custom([0.d0, 0.2d0, 0.4d0, 0.6d0, 0.8d0, &
                                         1.d0, 1.2d0, 1.4d0, 1.6d0, 1.8d0, &
                                         2.d0, 2.2d0, 2.4d0], &
                                       'ATLAS13TeV_HighMassDY_2D_Rapidity_mass1')

          histos(8) = plot_setup_custom([0.d0, 0.2d0, 0.4d0, 0.6d0, 0.8d0, &
                                         1.d0, 1.2d0, 1.4d0, 1.6d0, 1.8d0, &
                                         2.d0, 2.2d0, 2.4d0], &
                                       'ATLAS13TeV_HighMassDY_2D_Rapidity_mass2')

          histos(9) = plot_setup_custom([0.d0, 0.2d0, 0.4d0, 0.6d0, 0.8d0, &
                                         1.d0, 1.2d0, 1.4d0, 1.6d0, 1.8d0, &
                                         2.d0, 2.2d0, 2.4d0], &
                                       'ATLAS13TeV_HighMassDY_2D_Rapidity_mass3')

          histos(10) = plot_setup_custom([0.d0, 0.2d0, 0.4d0, 0.6d0, 0.8d0, &
                                          1.d0, 1.2d0, 1.4d0, 1.6d0, 1.8d0, &
                                          2.d0, 2.2d0, 2.4d0], &
                                        'ATLAS13TeV_HighMassDY_2D_Rapidity_mass4')

          histos(11) = plot_setup_custom([0.d0, 0.3d0, 0.6d0, 0.9d0, &
                                         1.2d0, 1.5d0, 1.8d0, 2.1d0, &
                                         2.4d0], &
                                        'ATLAS13TeV_HighMassDY_2D_Rapidity_mass5')

          histos(12) = plot_setup_custom([130.d0, 150.d0, &
                                       175.d0, 200.d0, 230.d0, 260.d0, 300.d0, &
                                       380.d0, 500.d0, 700.d0, 1000.d0, 1500.d0, &
                                       2000.d0, 2500.d0, 3000.d0, 3500.d0, 4000.d0, &
                                       4500.d0, 5000.d0, 5500.d0, 6000.d0, 6500.d0, &
                                       7000.d0], &
                                       'ATLAS13p6TeV_ZPrime_1D_mass')


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
          real(dp) :: pt_leading, pt_subleading, CosThetaCS

          real(dp) :: isY1, isY2, isY3, isY4, isY5, isY6
          real(dp) :: isATL8, isATL13
          real(dp) :: isATL7Y1, isATL7Y2, isATL7Y3, isATL7
          real(dp) :: isCMS7, isCMS8, isCMS13
          real(dp) :: isCMSY1, isCMSY2, isCMSY3, isCMSY4, isCMSY5
          real(dp) :: isLHCb
          integer isATLAS7TeV,isATLAS8TeV,isATLAS13TeV
          integer isCMS7TeV,isCMS8TeV,isCMS13TeV
          integer isLHCb13TeV
          real(dp) :: isHighMassDY
          real(dp) :: isHighMassDY_mass1, isHighMassDY_mass2, isHighMassDY_mass3
          real(dp) :: isHighMassDY_mass4, isHighMassDY_mass5

          pt34 = pttwo(3,4,p)
          y34=yraptwo(3,4,p)

          delphi34 = delphi(p(3,:),p(4,:))
          phiacop = 2._dp*atan(sqrt((1._dp+cos(delphi34))/(1._dp-cos(delphi34))))
          costhetastar = tanh((etarap(3,p)-etarap(4,p))/2._dp)
          phistar = tan(phiacop/2._dp)*sin(acos(costhetastar))

          m34=dsqrt((p(3,4)+p(4,4))**2-(p(3,1)+p(4,1))**2-(p(3,2)+p(4,2))**2-(p(3,3)+p(4,3))**2)

          CosThetaCS = 1._dp/(dsqrt(m34*m34+pt34*pt34)*m34) * ((p(3,4)+p(3,3))*(p(4,4)-p(4,3))-(p(4,4)+p(4,3))*(p(3,4)-p(3,3)));
          CosThetaCS = CosThetaCS * y34 / abs(y34);

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

          if (pt3 >= pt4) then
            pt_leading = pt3
            pt_subleading = pt4
          else
            pt_leading = pt4
            pt_subleading = pt3
          endif

          isHighMassDY = 0.0d0
          isHighMassDY_mass1 = 0.0d0
          isHighMassDY_mass2 = 0.0d0
          isHighMassDY_mass3 = 0.0d0
          isHighMassDY_mass4 = 0.0d0
          isHighMassDY_mass5 = 0.0d0

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 116.0d0 .and. m34 < 5000.0d0) then
            isHighMassDY = 1.0d0
          else
            isHighMassDY = 0.0d0
          endif

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 116.0d0 .and. m34 < 150.0d0) then
            isHighMassDY_mass1 = 1.0d0
          else
            isHighMassDY_mass1 = 0.0d0
          endif

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 150.0d0 .and. m34 < 200.0d0) then
            isHighMassDY_mass2 = 1.0d0
          else
            isHighMassDY_mass2 = 0.0d0
          endif

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 200.0d0 .and. m34 < 300.0d0) then
            isHighMassDY_mass3 = 1.0d0
          else
            isHighMassDY_mass3 = 0.0d0
          endif

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 300.0d0 .and. m34 < 500.0d0) then
            isHighMassDY_mass4 = 1.0d0
          else
            isHighMassDY_mass4 = 0.0d0
          endif

          if(pt_leading > 40.0d0 .and. pt_subleading > 30.0d0 .and. abs(eta3) < 2.5d0 .and. abs(eta4) < 2.5d0 .and. m34 > 500.0d0 .and. m34 < 1500.0d0) then
            isHighMassDY_mass5 = 1.0d0
          else
            isHighMassDY_mass5 = 0.0d0
          endif

          ids = histos
          vals = [m34, CosThetaCS, CosThetaCS, CosThetaCS, CosThetaCS, CosThetaCS, &
                  y34, y34, y34, y34, y34, &
                  m34]

          wts  = [wt*isHighMassDY, &
                  wt*isHighMassDY_mass1, wt*isHighMassDY_mass2, wt*isHighMassDY_mass3, &
                  wt*isHighMassDY_mass4, wt*isHighMassDY_mass5, &
                  wt*isHighMassDY_mass1, wt*isHighMassDY_mass2, wt*isHighMassDY_mass3, &
                  wt*isHighMassDY_mass4, wt*isHighMassDY_mass5, &
                  wt]

      end subroutine

end module
