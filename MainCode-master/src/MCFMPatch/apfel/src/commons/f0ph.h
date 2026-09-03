*     -*-fortran-*-
*
*     PDFs in the physical basis at the initial scale on the interpolation grid
*
      double precision f0ph(-6:6,0:nint_max)
      double precision f0lep(-3:3,0:nint_max)
      double precision f0phgrid(-6:6,0:nint_max,1:10)
      double precision f0lepgrid(-3:3,0:nint_max,1:10)
*
      common / pdf0APFEL / f0ph,f0lep,f0phgrid,f0lepgrid
