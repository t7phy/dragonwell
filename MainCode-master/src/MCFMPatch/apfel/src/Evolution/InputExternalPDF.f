C yfu
      subroutine inputexternalpdf(LHAsub)

      include "../commons/grid.h"
      include "../commons/pdfset.h"
      include "../commons/f0ph.h"
      include "../commons/fph.h"
      include "../commons/Replica.h"
      include "../commons/Evs.h"
      include "../commons/Nf_FF.h"
      include "../commons/MaxFlavourPDFs.h"
      include "../commons/IntrinsicCharm.h"

      integer alpha
      integer ifl,ilept
      double precision f0(-6:6),fext0(-6:7),flext0(-3:3),xfxQ

      interface
         subroutine LHAsub(x,Q,res)
           implicit none
           double precision x,Q
           double precision res(*)
         end subroutine LHAsub
      end interface

      do igrid = 1, ngrid
         do alpha=0,nin(igrid)
            call LHAsub(xg(igrid,alpha), 1.295d0, f0)
            do ifl=-6,6
               f0phgrid(ifl,alpha,igrid) = f0(ifl)
            enddo
            do ilept=-3,3
               f0lepgrid(ilept,alpha,igrid) = 0d0
            enddo
         enddo
      enddo

      return
      end
