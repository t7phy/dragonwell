#include "Figure/Figure.h"

void figure1d()
{
 Figure* myFigure;

 myFigure = new Figure(FigureName, XTitle, YTitle);
 myFigure->saveFigure();
 myFigure->SetMode("SINGLE");
 myFigure->SetPlot("E0");
 myFigure->SetLegendPosition(0.2, 0.6, 0.4, 0.8);
 myFigure->Input(1, RootName, HistName, LegendName);
 myFigure->Draw();
}
