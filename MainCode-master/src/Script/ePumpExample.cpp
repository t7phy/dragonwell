#include "/home/yfu/figure/Figure.h"

void figure()
{
 Figure* f;

 f = new Figure("update_same.pdf", "z", "#chi^{2}");
 f->SetMode("CUSTOM");
 f->InputTF1(1, "parabola.root", "f1", "original");
 f->InputTF1(2, "parabola.root", "f2", "updated");
 f->Compare("MultiSimple");
 f->AddLine(1, -1, 100, 1, 100);
 f->AddArrow(1, -0.5, 120, 0.5, 120, "<>", kGreen+2);
 f->AddArrow(2, 0.0, 0, 0.0, 100, "<>", kGreen+2);
 f->SetLegendPosition(0.05, 0.8, 0.25, 0.95);
 f->Draw();

 f = new Figure("update_different.pdf", "z", "#chi^{2}");
 f->SetMode("CUSTOM");
 f->InputTF1(1, "parabola.root", "f1", "original");
 f->InputTF1(2, "parabola.root", "f3", "updated");
 f->Compare("MultiSimple");
 f->AddLine(1, -1, 100, 1, 100);
 f->AddArrow(1, 0.1875, 4.6875, 0.1875, 100, "<>", kGreen+2);
 f->AddArrow(2, -0.300641, 120, 0.675641, 120, "<>", kGreen+2);
 f->SetLegendPosition(0.05, 0.8, 0.25, 0.95);
 f->Draw();


}
