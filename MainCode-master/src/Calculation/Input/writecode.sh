#!/bin/bash

nInit=51;
nFinal=100

for((i=${nInit};i<=${nFinal};i++)); do
echo "extern \"C\" void threadpdf${i}_(const double& , const double& , double* );"
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo "extern \"C\" void threadpdfpbar${i}_(const double& , const double& , double* );"
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo "extern \"C\" double threadalphas${i}_(const double& Q);"
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo "void threadpdf${i}_(const double& x, const double& Q, double* xf)"
echo "{"
echo "   for(int i = -6; i <= 6; i++){"
echo "     if(abs(i) >= 4){"
echo "       if(Q > ThreadQCDInstance[${i}]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[${i}]->xfxQ(i, x, Q);"
echo "     }"
echo "     else{"
echo "       xf[i + 6] = ThreadCTEQPDFInstance[${i}]->xfxQ(i, x, Q);"
echo "     }"
echo "   }"
echo "}"
echo ""
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo "void threadpdfpbar${i}_(const double& x, const double& Q, double* xf)"
echo "{"
echo " double pdf[13];"
echo " threadpdf${i}_(x, Q, pdf);"
echo " for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];"
echo "}"
echo ""
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo "double threadalphas${i}_(const double& Q)"
echo "{"
echo " return ThreadCTEQPDFInstance[${i}]->CT14Alphas(Q);"
echo "}"
echo ""
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo " else if(iThread == ${i}) xsec = ApplGridMap[GridName]->vconvolute( threadpdf${i}_, threadalphas${i}_, order);"
done

echo ""

for((i=${nInit};i<=${nFinal};i++)); do
echo " else if(iThread == ${i}) xsec = ApplGridMap[GridName]->vconvolute( threadpdf${i}_, threadpdfpbar${i}_, threadalphas${i}_, order);"
done

