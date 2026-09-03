#include "Calculation/CTUtil.h"

double CTUtil::dilog(double x)
{
 int ncall = 0;
 double pi6 = 1.644934066848226;
 double een = 1.0;
 double vier = 0.25;
 double u = 0.0;
 vector<double> b(9);

 double Value = 0.0;

 if(ncall == 0){// goto 2
   b.at(1)=een;
   b.at(2)=een/36.0;
   b.at(3)=-een/3600.0;
   b.at(4)=een/211680.0;
   b.at(5)=-een/(30.0*362880.0);
   b.at(6)=5.0/(66.0*39916800.0);
   b.at(7)=-691.0/(2730.0*39916800.0*156.0);
   b.at(8)=een/(39916800.0*28080.0);
   ncall=1;
 }

 if(x < 0){// goto 3
   if(x > -een){// goto 5
     double y=een/(een-x);
     double z=-log(y);
     double z2=z*z;
     Value = -z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
     +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een)-z2*vier;
     return Value;
   }
   double y=een/(een-x);
   double z=-log(een-y);
   double z2=z*z;
   u=log(y);
   Value = z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
   +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een)-z2*vier-u*(z+0.5*u)-pi6;
   return Value;
 }
 else if(x > 0.5){// goto 4
   if(x >= een){// goto 10
     if(x == een){// goto 20
       Value = pi6;
       return Value;
     }
     double xx = 1.0 / x;
     if(x > 2.0){// goto 11
       u=log(x);
       double z=-log(1.0-xx);
       // goto 7
       double z2=z*z;
       Value = z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
       +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een)-z2*vier;
       if(x > een) Value = -Value - 0.5*u*u+2.0*pi6;
       return Value;
     }
     else{// not goto 11
       double z=log(x);
       double y=1.0-xx;

       // goto 6
       u=log(y);
       double z2=z*z;
       Value = -z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
       +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een-u)+z2*vier+pi6;
       if(x > een) Value = -Value - 0.5*z*z + pi6*2.0;
       return Value;
     }
   }
   else{// not goto 10, but enter 6
     double y=een-x;
     double z=-log(x);
     u=log(y);
     double z2=z*z;
     Value = -z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
     +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een-u)+z2*vier+pi6;
     if(x > een) Value = -Value - 0.5*z*z + pi6*2.0;
     return Value;
   }
 }

 // not goto 3 and not goto 4
 double z=-log(1.-x);
 double z2=z*z;
 Value = z*(z2*(z2*(z2*(z2*(z2*(z2*(z2*b.at(8)+b.at(7))+b.at(6))
 +b.at(5))+b.at(4))+b.at(3))+b.at(2))+een)-z2*vier;
 if(x > een) Value = -Value - 0.5*u*u+2.0*pi6;
 return Value;

}
