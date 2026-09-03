#include <fstream>
#include <iostream>
#include "RootCommon.h"
#include "FeynmanDiagram/fd.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"Usage: ./WWuDiagram name"<<endl;
   return 0;
 }

 TString Diagram = argv[1];

 if(Diagram == "WWu"){

   ////////////////////
   //  WW u-channel  //
   ////////////////////

   ofstream fout;
   fout.open("WWu.eps");
  
   page pg;
   FeynDiagram fd(pg);
   xy e1(-8,5), e2(-8,-5), e3(8,5), e4(8,-5);
   vertex_dot v1(fd,0,2.5), v2(fd,0,-2.5);
  
   line_plain f1(fd,e1,v1);
   text tx1(fd,(char *)"q",xy(-7,5.5));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f2(fd,v1,v2);
   text tx2(fd,(char *)"\\overline{q}",xy(-7,-5.5));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f3(fd,v2,e2);
  
   line_wiggle W1(fd,v1,e4);
   text tx4(fd,(char *)"W^+", xy(6,6));
   tx4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_wiggle W2(fd,v2,e3);
   text tx5(fd,(char *)"W^-", xy(6,-6));
   tx5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();

 }

 if(Diagram == "WWt"){

   ////////////////////
   //  WW t-channel  //
   ////////////////////
  
   ofstream fout;
   fout.open("WWt.eps");
  
   page pg;
   FeynDiagram fd(pg);
   xy e1(-8,5), e2(-8,-5), e3(8,5), e4(8,-5);
   vertex_dot v1(fd,0,2.5), v2(fd,0,-2.5);
  
   line_plain f1(fd,e1,v1);
   text tx1(fd,(char *)"q",xy(-7,5.5));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f2(fd,v1,v2);
   text tx2(fd,(char *)"\\overline{q}",xy(-7,-5.5));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f3(fd,v2,e2);
  
   line_wiggle W1(fd,v1,e3);
   text tx4(fd,(char *)"W^+", xy(6,6));
   tx4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_wiggle W2(fd,v2,e4);
   text tx5(fd,(char *)"W^-", xy(6,-6));
   tx5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WWbox"){

   //////////////
   //  WW box  //
   //////////////

   ofstream fout;
   fout.open("WWbox.eps");

   page pg;
   FeynDiagram fd(pg);
   xy e1(-8,3), e2(-8,-3), e3(8,3), e4(8,-3);
   vertex_dot v1(fd,-3,3), v2(fd,-3,-3), v3(fd,3,-3), v4(fd,3,3);

   line_spring f1(fd,e1,v1);
   text tx1(fd,(char *)"g",xy(-7,4.5));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");

   line_spring f2(fd,e2,v2);
   text tx2(fd,(char *)"g",xy(-7,-4.5));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");

   line_plain f3(fd,v1,v2);
   line_plain f4(fd,v2,v3);
   line_plain f5(fd,v3,v4);
   line_plain f6(fd,v4,v1);

   line_wiggle W1(fd,v3,e4);
   text tx4(fd,(char *)"W^+", xy(6,4.5));
   tx4.fontname.set((char *)"NewCenturySchlbk-Italic");

   line_wiggle W2(fd,v4,e3);
   text tx5(fd,(char *)"W^-", xy(6,-4.5));
   tx5.fontname.set((char *)"NewCenturySchlbk-Italic");

   pg.output(fout);
   fout.close();
 }

 if(Diagram == "Zgamma"){

   ///////////////
   //  Z/gamma  //
   ///////////////
  
   ofstream fout;
   fout.open("Zgamma.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   xy p1(-12,5.3), p2(-12,-5.3);
   blob b1(fd,xy(-8.8,5.3), 0.8, 0.8);
   blob b2(fd,xy(-8.8,-5.3), 0.8, 0.8);
   b1.addshading_lines(45);
   b2.addshading_lines(45);
  
   line_plain pf1(fd,p1,xy(-9.6,5.3));
   text h1(fd,(char *)"h_A",xy(-13.5,5.3));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf2(fd,p2,xy(-9.6,-5.3));
   text h2(fd,(char *)"h_B",xy(-13.5,-5.3));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain jet1(fd,xy(-8,5.4),xy(0,5.7));
   line_plain jet2(fd,xy(-8,5.4),xy(0.5,6.9));
   line_plain jet3(fd,xy(-8,-5.4),xy(0,-5.7));
   line_plain jet4(fd,xy(-8,-5.4),xy(-0.5,-6.9));
  
   xy e1(-8,5), e2(-8,-5), e3(8,5), e4(8,-5);
   vertex_dot v1(fd,-4,0), v2(fd,4,0);
  
   line_plain f1(fd,e1,v1);
   text tx1(fd,(char *)"q",xy(-5,3));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f2(fd,v1,e2);
   text tx2(fd,(char *)"\\overline{q}",xy(-5,-3));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_wiggle f3(fd,v1,v2);
   text tx3(fd,(char *)"Z/\\gamma^*", xy(-1.5,1));
   tx3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain W1(fd,v2,e3);
   text tx4(fd,(char *)"l^-", xy(6.5,5.5));
   tx4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain W2(fd,e4,v2);
   text tx5(fd,(char *)"l^+", xy(6.5,-5.5));
   tx5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "ResumGluons"){

   //////////////////
   // Resum gluons //
   //////////////////
  
   ofstream fout;
   fout.open("ResumGluons.eps");
  
   page pg;
   FeynDiagram fd(pg, 1, 4, 4);
   fd.line_plain_arrowon.setfalse();
  
   double scale = 0.7;
   double xpos = 2.0;
  
   line_plain l1(fd, xy((-10 + xpos)/scale, 5/scale), xy((-7 + xpos)/scale, 0/scale));
   line_plain l2(fd, xy((-10 + xpos)/scale, -5/scale), xy((-7 + xpos)/scale, 0/scale));
   line_wiggle b1(fd, xy((-7 + xpos)/scale, 0/scale), xy((-3 + xpos)/scale, 0/scale));
  
   text tx1(fd,(char *)"+", xy((-1 + xpos)/scale, 0/scale));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");
   tx1.fontsize.scale(1.5);
  
   line_plain l3(fd, xy((1 + xpos)/scale, 5/scale), xy((4 + xpos)/scale, 0/scale));
   line_plain l4(fd, xy((1 + xpos)/scale, -5/scale), xy((4 + xpos)/scale, 0/scale));
   line_wiggle b2(fd, xy((4 + xpos)/scale, 0/scale), xy((8 + xpos)/scale, 0/scale));
   line_spring g1(fd, xy((1 + xpos + 1.5)/scale, (-5+1.5*5/3)/scale), xy((1 + xpos + 5)/scale, (-5+1.5*5/3)/scale));
  
   text tx2(fd,(char *)"+", xy((10 + xpos)/scale, 0/scale));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");
   tx2.fontsize.scale(1.5);
  
   line_plain l5(fd, xy((12 + xpos)/scale, 5/scale), xy((15 + xpos)/scale, 0/scale));
   line_plain l6(fd, xy((12 + xpos)/scale, -5/scale), xy((15 + xpos)/scale, 0/scale));
   line_wiggle b3(fd, xy((15 + xpos)/scale, 0/scale), xy((19 + xpos)/scale, 0/scale));
   line_spring g2(fd, xy((12 + xpos + 1.5)/scale, (-5+1.5*5/3)/scale), xy((12 + xpos + 5)/scale, (-5+1.5*5/3)/scale));
   line_spring g3(fd, xy((12 + xpos + 1.5)/scale, (5-1.5*5/3)/scale), xy((12 + xpos + 5)/scale, (5-1.5*5/3)/scale));
  
   text tx3(fd,(char *)"+", xy((21 + xpos)/scale, 0/scale));
   tx3.fontname.set((char *)"NewCenturySchlbk-Italic");
   tx3.fontsize.scale(1.5);
  
   line_plain l7(fd, xy((23 + xpos)/scale, 5/scale), xy((26 + xpos)/scale, 0/scale));
   line_plain l8(fd, xy((23 + xpos)/scale, -5/scale), xy((26 + xpos)/scale, 0/scale));
   line_wiggle b4(fd, xy((26 + xpos)/scale, 0/scale), xy((30 + xpos)/scale, 0/scale));
   line_spring g4(fd, xy((23 + xpos + 1)/scale, (-5+1.0*5/3)/scale), xy((23 + xpos + 5)/scale, (-5+1.0*5/3)/scale));
   line_spring g5(fd, xy((23 + xpos + 1.5)/scale, (5-1.5*5/3)/scale), xy((23 + xpos + 5)/scale, (5-1.5*5/3)/scale));
   line_spring g6(fd, xy((23 + xpos + 2)/scale, (-5+2.0*5/3)/scale), xy((23 + xpos + 5)/scale, (-5+2.0*5/3)/scale));
  
   text tx4(fd,(char *)"+ ...", xy((32 + xpos)/scale, 0/scale));
   tx4.fontname.set((char *)"NewCenturySchlbk-Italic");
   tx4.fontsize.scale(1.5);
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "FactorizationResum"){

   ///////////////////////////////
   // Factorization Resummation //
   ///////////////////////////////
  
   ofstream fout;
   fout.open("FactorizationResum.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   xy p1(-12,8), p2(-12,-8);
   blob b1(fd,xy(-4,6.5), 1.2, 1.2);
   blob b2(fd,xy(-4,-6.5), 1.2, 1.2);
   b1.addshading_lines(45);
   b2.addshading_lines(45);
   xy p3(-4, 6.5), p4(-4, -6.5);
  
   blob b3(fd,xy(-10, 0), 1.2, 1.2);
   b3.addshading_lines(45);
  
   blob b4(fd,xy(4, 0), 1.2, 1.2);
   b4.addshading_lines(45);
  
   line_plain pf1(fd,p1,b1.location(165));
   text h1(fd,(char *)"C",xy(-4.2,8.5));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf2(fd,p2,b2.location(195));
   text h2(fd,(char *)"C",xy(-4.2,-4.5));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   text h3(fd,(char *)"S",xy(-10.2,2));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   text h4(fd,(char *)"H",xy(3.8,2));
   h4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf3(fd,b1.location(330),b4.location(150));
   line_plain pf4(fd,b2.location(30),b4.location(210));
  
   line_wiggle W2(fd,b4.location(0),xy(12,0));
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "SplittingKernal1"){

   //////////////////////
   // Splitting Kernal //
   //////////////////////
  
   ofstream fout;
   fout.open("SplittingKernal1.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_plain pf1(fd,xy(-5,-5),xy(0,0));
   line_plain pf2(fd,xy(-5,-3.5),xy(-1.5,0));
   text h1(fd,(char *)"p",xy(-5,-1));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf3(fd,xy(0,0),xy(5,5));
   line_plain pf4(fd,xy(0,1.5),xy(3.5,5));
   text h2(fd,(char *)"xp",xy(0,4));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_spring pf5(fd,xy(0,0),xy(5,-5));
   line_plain pf6(fd,xy(1.5,0),xy(5,-3.5));
   text h3(fd,(char *)"(1-x)p",xy(3,0));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "SplittingKernal2"){

   ofstream fout;
   fout.open("SplittingKernal2.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_plain pf1(fd,xy(-5,-5),xy(0,0));
   line_plain pf2(fd,xy(-5,-3.5),xy(-1.5,0));
   text h1(fd,(char *)"p",xy(-5,-1));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_spring pf3(fd,xy(0,0),xy(5,5));
   line_plain pf4(fd,xy(0,1.5),xy(3.5,5));
   text h2(fd,(char *)"xp",xy(0,4));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf5(fd,xy(0,0),xy(5,-5));
   line_plain pf6(fd,xy(1.5,0),xy(5,-3.5));
   text h3(fd,(char *)"(1-x)p",xy(3,0));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "SplittingKernal3"){

   ofstream fout;
   fout.open("SplittingKernal3.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_spring pf1(fd,xy(-5,-5),xy(0,0));
   line_plain pf2(fd,xy(-5,-3.5),xy(-1.5,0));
   text h1(fd,(char *)"p",xy(-5,-1));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf3(fd,xy(0,0),xy(5,5));
   line_plain pf4(fd,xy(0,1.5),xy(3.5,5));
   text h2(fd,(char *)"xp",xy(0,4));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf5(fd,xy(5,-5),xy(0,0));
   line_plain pf6(fd,xy(1.5,0),xy(5,-3.5));
   text h3(fd,(char *)"(1-x)p",xy(3,0));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "SplittingKernal4"){

   ofstream fout;
   fout.open("SplittingKernal4.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_spring pf1(fd,xy(-5,-5),xy(0,0));
   line_plain pf2(fd,xy(-5,-3.5),xy(-1.5,0));
   text h1(fd,(char *)"p",xy(-5,-1));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_spring pf3(fd,xy(0,0),xy(5,5));
   line_plain pf4(fd,xy(0,1.5),xy(3.5,5));
   text h2(fd,(char *)"xp",xy(0,4));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_spring pf5(fd,xy(0,0),xy(5,-5));
   line_plain pf6(fd,xy(1.5,0),xy(5,-3.5));
   text h3(fd,(char *)"(1-x)p",xy(3,0));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "Factorization"){

   ///////////////////
   // Factorization //
   ///////////////////
  
   ofstream fout;
   fout.open("Factorization.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   xy p1(-12,5.3), p2(-12,-5.3);
   blob b1(fd,xy(-8.8,5.3), 0.8, 0.8);
   blob b2(fd,xy(-8.8,-5.3), 0.8, 0.8);
   b1.addshading_lines(45);
   b2.addshading_lines(45);
  
   line_plain pf1(fd,p1,xy(-9.6,5.3));
   text h1(fd,(char *)"h_A(P_1)",xy(-13.5,6.5));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain pf2(fd,p2,xy(-9.6,-5.3));
   text h2(fd,(char *)"h_B(P_2)",xy(-13.5,-7));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain jet1(fd,xy(-8,5.4),xy(0,5.7));
   line_plain jet2(fd,xy(-8,5.4),xy(0.5,6.9));
   line_plain jet3(fd,xy(-8,-5.4),xy(0,-5.7));
   line_plain jet4(fd,xy(-8,-5.4),xy(-0.5,-6.9));
  
   xy e1(-8,5), e2(-8,-5), e3(8,5), e4(8,-5);
   vertex_dot v1(fd,-4,0);
  
   line_plain f1(fd,e1,v1);
   text tx1(fd,(char *)"p_1=x_1P_1",xy(-11,2));
   tx1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f2(fd,v1,e2);
   text tx2(fd,(char *)"p_2=x_2P_2",xy(-11,-2));
   tx2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_wiggle f3(fd,v1,xy(4,0));
   line_plain f4(fd,xy(-2,1),xy(2,1));
   text tx3(fd,(char *)"q", xy(0,2));
   tx3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "DIS"){

   /////////
   // DIS //
   /////////
  
   ofstream fout;
   fout.open("DIS.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   xy p1(-7,6), p2(2,5);
   xy p3(-8,-5), p4(2,-2);
   blob b1(fd,xy(-2,-5), 1, 1);
   b1.addshading_lines(45);
  
   line_plain f1(fd,p1,p2);
   text h1(fd,(char *)"e^\\pm",xy(-8,6));
   h1.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f2(fd,p3,b1.location(180));
   text h2(fd,(char *)"p",xy(-8,-4));
   h2.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   text h3(fd,(char *)"\\gamma^{*}/Z,W^\\pm",xy(-3,1.5));
   h3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   text h4(fd,(char *)"e^\\pm,\\nu_e",xy(10,8));
   h4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   text h5(fd,(char *)"X",xy(9,-6.5));
   h5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   line_plain f3(fd,p2,xy(10,7));
   line_wiggle w(fd,p2,p4);
  
   line_plain f4(fd,b1.location(45),p4);
   line_plain f5(fd,p4,xy(8,-2));
  
   line_plain f6(fd,b1.location(0),xy(8,-6));
   line_plain f7(fd,b1.location(-20),xy(8,-7));
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WWgamma"){

   ////////////////////////
   // Non-Abelian Vertex //
   ////////////////////////
  
   ofstream fout;
   fout.open("WWgamma.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_wiggle w1(fd,xy(0,0),xy(5,0));
   line_wiggle w2(fd,xy(-2.5,-2.5*sqrt(3.0)),xy(0,0));
   line_wiggle w3(fd,xy(-2.5,2.5*sqrt(3.0)),xy(0,0));
   vertex_dot v1(fd,0,0);
  
   text t1(fd,(char *)"W^{ \\plus}",xy(-4.5,-2.5*sqrt(3.0)-0.5));
   t1.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t2(fd,(char *)"W^{ \\minus}",xy(-4.5,2.5*sqrt(3.0)-0.5));
   t2.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t3(fd,(char *)"\\gamma",xy(5.8,-0.3));
   t3.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WWWW"){

   ofstream fout;
   fout.open("WWWW.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_wiggle w1(fd,xy(0,0),xy(5.0/sqrt(2.0),5.0/sqrt(2.0)));
   line_wiggle w2(fd,xy(0,0),xy(-5.0/sqrt(2.0),5.0/sqrt(2.0)));
   line_wiggle w3(fd,xy(0,0),xy(5.0/sqrt(2.0),-5.0/sqrt(2.0)));
   line_wiggle w4(fd,xy(0,0),xy(-5.0/sqrt(2.0),-5.0/sqrt(2.0)));
   vertex_dot v1(fd,0,0);
  
   text t1(fd,(char *)"W^{ \\plus}",xy(-5.0/sqrt(2.0)-2.0,-5.0/sqrt(2.0)-1.3));
   t1.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t2(fd,(char *)"W^{ \\plus}",xy(5.0/sqrt(2.0)+0.5,-5.0/sqrt(2.0)-1.3));
   t2.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t3(fd,(char *)"W^{ \\minus}",xy(-5.0/sqrt(2.0)-2.0,5.0/sqrt(2.0)));
   t3.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t4(fd,(char *)"W^{ \\minus}",xy(5.0/sqrt(2.0)+0.5,5.0/sqrt(2.0)));
   t4.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WZ_s"){

   ////////////////
   // WZ diagram //
   ////////////////
  
   ofstream fout;
   fout.open("WZ_s.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_wiggle w1(fd,xy(0,0),xy(5,0));
   line_plain f1(fd,xy(-2.5,-2.5*sqrt(3.0)),xy(0,0));
   line_plain f2(fd,xy(0,0),xy(-2.5,2.5*sqrt(3.0)));
   vertex_dot v1(fd,0,0);
   vertex_dot v2(fd,5,0);
   line_wiggle w2(fd,xy(5,0),xy(7.5,2.5*sqrt(3.0)));
   line_wiggle w3(fd,xy(5,0),xy(7.5,-2.5*sqrt(3.0)));
  
   text t1(fd,(char *)"q",xy(-4.5,-2.5*sqrt(3.0)-0.5));
   t1.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t2(fd,(char *)"q^{\\prime}",xy(-4.5,2.5*sqrt(3.0)-0.5));
   t2.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t3(fd,(char *)"W",xy(2.0,-2.0));
   t3.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t4(fd,(char *)"Z",xy(8,-2.5*sqrt(3.0)-0.5));
   t4.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t5(fd,(char *)"W",xy(8,2.5*sqrt(3.0)-0.5));
   t5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WZ_t"){

   ofstream fout;
   fout.open("WZ_t.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_plain f1(fd,xy(-7,-2.5*sqrt(3.0)),xy(0.0,-2.5*sqrt(3.0)));
   line_plain f2(fd,xy(0.0,-2.5*sqrt(3.0)),xy(0.0,2.5*sqrt(3.0)));
   line_plain f3(fd,xy(0.0,2.5*sqrt(3.0)),xy(-7,2.5*sqrt(3.0)));
  
   line_wiggle w1(fd,xy(0,-2.5*sqrt(3.0)),xy(7,-2.5*sqrt(3.0)));
   line_wiggle w2(fd,xy(0,2.5*sqrt(3.0)),xy(7,2.5*sqrt(3.0)));
  
   vertex_dot v1(fd,0,-2.5*sqrt(3.0));
   vertex_dot v2(fd,0,2.5*sqrt(3.0));
  
   text t1(fd,(char *)"q",xy(-8,-2.5*sqrt(3.0)-0.5));
   t1.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t2(fd,(char *)"q^{\\prime}",xy(-8,2.5*sqrt(3.0)-0.5));
   t2.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t3(fd,(char *)"q",xy(-1.0,0.0));
   t3.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t4(fd,(char *)"Z",xy(8,-2.5*sqrt(3.0)-0.5));
   t4.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t5(fd,(char *)"W",xy(8,2.5*sqrt(3.0)-0.5));
   t5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "WZ_u"){
   ofstream fout;
   fout.open("WZ_u.eps");
  
   page pg;
   FeynDiagram fd(pg);
  
   line_plain f1(fd,xy(-7,-2.5*sqrt(3.0)),xy(0.0,-2.5*sqrt(3.0)));
   line_plain f2(fd,xy(0.0,-2.5*sqrt(3.0)),xy(0.0,2.5*sqrt(3.0)));
   line_plain f3(fd,xy(0.0,2.5*sqrt(3.0)),xy(-7,2.5*sqrt(3.0)));
  
   line_wiggle w1(fd,xy(0,-2.5*sqrt(3.0)),xy(7,2.5*sqrt(3.0)));
   line_wiggle w2(fd,xy(0,2.5*sqrt(3.0)),xy(7,-2.5*sqrt(3.0)));
  
   vertex_dot v1(fd,0,-2.5*sqrt(3.0));
   vertex_dot v2(fd,0,2.5*sqrt(3.0));
  
   text t1(fd,(char *)"q",xy(-8,-2.5*sqrt(3.0)-0.5));
   t1.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t2(fd,(char *)"q^{\\prime}",xy(-8,2.5*sqrt(3.0)-0.5));
   t2.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t3(fd,(char *)"q",xy(-1.0,0.0));
   t3.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t4(fd,(char *)"Z",xy(8,-2.5*sqrt(3.0)-0.5));
   t4.fontname.set((char *)"NewCenturySchlbk-Italic");
   text t5(fd,(char *)"W",xy(8,2.5*sqrt(3.0)-0.5));
   t5.fontname.set((char *)"NewCenturySchlbk-Italic");
  
   pg.output(fout);
   fout.close();
 }

 if(Diagram == "qg"){
   ofstream fout;
   fout.open("qg.eps");

   page pg;
   FeynDiagram fd(pg);

   line_plain f1(fd, xy(-3,4), xy(0,0));
   line_plain f2(fd, xy(0,0), xy(-1.5,-2));
   line_plain f3(fd, xy(-1.5,-2), xy(0.5,-5));
   line_spring g(fd, xy(-6,-2), xy(-1.5,-2));
   line_wiggle Z(fd, xy(0,0), xy(5,0));
   line_plain f4(fd, xy(5,0), xy(8,3));
   line_plain f5(fd, xy(8,-3), xy(5,0));
   vertex_dot v1(fd,0,0);
   vertex_dot v2(fd,5,0);
   vertex_dot v3(fd,-1.5,-2);

   pg.output(fout);
   fout.close();

 }

 return 1;
}

