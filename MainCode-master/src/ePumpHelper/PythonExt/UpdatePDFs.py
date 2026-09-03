import PyePump

ep = PyePump.PyePump()
ep.Initialize("test")

BaseName = "tabsCT18Am248_1164/"
LMScanDrawList = [BaseName + "E160",
                  BaseName + "E542",
                  BaseName + "E545",
                  BaseName + "E544",
                  BaseName + "E514",
                  BaseName + "E504",
                  BaseName + "E147",
                  BaseName + "E102",
                  BaseName + "E101",
                  BaseName + "E110",
                  BaseName + "E248",]

ep.InputLMScanDrawList(LMScanDrawList)

ep.Update()
ep.UpdateAlphaS("testAlphaS")

# PDFLMScanModule(int flavor, double x, double Q, int isUpdate)
ep.PDFLMScanModule(0, 0.01, 125.0, 0)
ep.PDFLMScanModule(0, 0.01, 125.0, 1)

# UpdateAlphaSLMScanPDF(int flavor, double x, double Q)
ep.UpdateAlphaSLMScanPDF(0, 0.01, 125.0)

# AlphaSObservableCorrelation(const char* name, int iPoint, const char* legend)
ep.AlphaSObservableCorrelation(BaseName + "ggHiggsXsec", 0, "#sigma(gg #rightarrow H) [pb]")
