cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0074 NEW)
project(loopMC)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR} CACHE PATH "Install prefix" FORCE)
endif()

find_package(ROOT)
include_directories(${ROOT_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

option(USE_LHAPDF "Enable LHAPDF support" ON)
option(USE_LWTNN "Enable lwtnn support" OFF)
option(USE_TMVA "Enable ROOT TMVA support" ON)
option(USE_ROOFIT "Enable ROOT RooFit/RooStats support" ON)
option(USE_APPLGRID "Enable APPLgrid support" ON)
option(USE_BAT "Enable Bayesian Analysis Toolkit support" ON)
option(USE_ROOUNFOLD "Enable RooUnfold support" OFF)
option(USE_HOPPET "Enable HOPPET support" ON)
option(USE_HOPPET_CXX "Enable the experimental HOPPET C++ interface" OFF)
option(USE_FNLO "Enable fastNLO support" ON)
option(USE_MINUIT2 "Enable ROOT Minuit2 support" ON)
option(USE_YAML "Enable yaml-cpp run-card support" ON)
option(USE_APFEL "Enable APFEL, APFELgrid, and APFEL++ support" ON)
option(USE_SWIG "Build SWIG-generated Python bindings" OFF)
option(USE_JSON "Enable nlohmann-json integration helpers" OFF)
option(USE_PINEAPPL "Enable PineAPPL support" ON)
option(USE_PYTHON "Build the pre-generated Python extension" OFF)

#LHAPDF
if(USE_LHAPDF)
    add_definitions(-DUSE_LHAPDF)
    set(LHAPDF_ROOT $ENV{LHAPDF_ROOT_DIR})
    set(LHAPDF_INCLUDE_DIRS $ENV{LHAPDF_ROOT_DIR}/include)
    include_directories(${LHAPDF_INCLUDE_DIRS})
endif(USE_LHAPDF)

#ApplGrid
if(USE_APPLGRID)
    add_definitions(-DUSE_APPLGRID)
    set(APPLGRID_ROOT $ENV{APPLGRID_ROOT_DIR})
    set(APPLGRID_INCLUDE_DIRS $ENV{APPLGRID_ROOT_DIR}/include)
    include_directories(${APPLGRID_INCLUDE_DIRS})
endif(USE_APPLGRID)

#FastNLO
if(USE_FNLO)
    add_definitions(-DUSE_FNLO)
    set(FASTNLO_ROOT $ENV{FASTNLO_ROOT_DIR})
    set(FASTNLO_INCLUDE_DIRS $ENV{FASTNLO_ROOT_DIR}/include)
    include_directories(${FASTNLO_INCLUDE_DIRS})
endif(USE_FNLO)

if(USE_YAML)
    add_definitions(-DUSE_YAML)
    find_package(yaml-cpp REQUIRED)
    set(yaml-cpp_LIBRARIES yaml-cpp::yaml-cpp)
endif(USE_YAML)

#HOPPET
if(USE_HOPPET)
    add_definitions(-DUSE_HOPPET)
    set(Hoppet_ROOT $ENV{Hoppet_ROOT_DIR})
    set(Hoppet_INCLUDE_DIRS $ENV{Hoppet_ROOT_DIR}/include)
    include_directories(${Hoppet_INCLUDE_DIRS})
endif(USE_HOPPET)

if(USE_HOPPET_CXX)
    add_definitions(-DUSE_HOPPET_CXX)
endif(USE_HOPPET_CXX)

#APFEL
if(USE_APFEL)
    add_definitions(-DUSE_APFEL)
    set(apfelxx_ROOT $ENV{apfelxx_ROOT_DIR})
    set(apfelxx_INCLUDE_DIRS $ENV{apfelxx_ROOT_DIR}/include)
    include_directories(${apfelxx_INCLUDE_DIRS})
endif(USE_APFEL)

#BAT
if(USE_BAT)
    add_definitions(-DUSE_BAT)
    set(BAT_ROOT $ENV{BAT_ROOT_DIR})
    set(BAT_INCLUDE_DIRS $ENV{BAT_ROOT_DIR}/include)
    include_directories(${BAT_INCLUDE_DIRS})
endif(USE_BAT)

#LWTNN
if(USE_LWTNN)
    add_definitions(-DUSE_LWTNN)
    set(LWTNN_ROOT $ENV{LWTNN_ROOT_DIR})
    set(LWTNN_INCLUDE_DIRS $ENV{LWTNN_ROOT_DIR}/include)
    set(LWTNN_LIBRARIES $ENV{LWTNN_ROOT_DIR}/lib/liblwtnn.so)
    include_directories(${LWTNN_INCLUDE_DIRS})
endif(USE_LWTNN)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#SWIG
if(USE_SWIG)
    cmake_policy(SET CMP0078 NEW)
    cmake_policy(SET CMP0086 NEW)
    find_package(SWIG REQUIRED)
    include(UseSWIG)
    find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
    include_directories(${Python3_INCLUDE_DIRS})
endif(USE_SWIG)

#PineAPPL
if(USE_PINEAPPL)
    add_definitions(-DUSE_PINEAPPL)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PINEAPPL REQUIRED IMPORTED_TARGET pineappl_capi)
endif(USE_PINEAPPL)

#JSON
if(USE_JSON)
    add_definitions(-DUSE_JSON)
    set(CMAKE_PREFIX_PATH $ENV{json_ROOT_DIR})
    find_package(nlohmann_json)
endif(USE_JSON)

#TMinuit
set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libMinuit.so")#for cvmfs

if(USE_MINUIT2)
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libMinuit2.so")#for cvmfs
endif(USE_MINUIT2)

#TMVA
if(USE_TMVA)
    add_definitions(-DUSE_TMVA)
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libTMVA.so")#for cvmfs
endif(USE_TMVA)

#RooFit
if(USE_ROOFIT)
    add_definitions(-DUSE_ROOFIT)
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFit.so")
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooStats.so")
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFitCore.so")
    #set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFitMore.so")
endif(USE_ROOFIT)

include_directories(include)
add_subdirectory(src)

#RooUnfold
if(USE_ROOUNFOLD)
    add_definitions(-DUSE_ROOUNFOLD)
    set(RooUnfold_ROOT $ENV{ROOUNFOLD_ROOT_DIR})
    set(RooUnfold_INCLUDE_DIRS $ENV{ROOUNFOLD_ROOT_DIR}/include)
    set(RooUnfold_LIBRARIES $ENV{ROOUNFOLD_ROOT_DIR}/lib/libRooUnfold.so)
    include_directories(${RooUnfold_INCLUDE_DIRS})
endif(USE_ROOUNFOLD)

add_executable(loopMC util/main.C)
target_link_libraries(loopMC Analysis SpecialHist TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS loopMC DESTINATION bin)

add_executable(PDFUncertainty util/PDFUnc.C)
target_link_libraries(PDFUncertainty Uncertainty ${ROOT_LIBRARIES})
install(TARGETS PDFUncertainty DESTINATION bin)

add_executable(ScaleUncertainty util/ScaleUnc.C)
target_link_libraries(ScaleUncertainty Uncertainty ${ROOT_LIBRARIES})
install(TARGETS ScaleUncertainty DESTINATION bin)

add_executable(AFBStw util/AFBStw.C)
target_link_libraries(AFBStw Uncertainty ${ROOT_LIBRARIES})
install(TARGETS AFBStw DESTINATION bin)

add_executable(GetResBosAngular util/GetResBosAngular.C)
target_link_libraries(GetResBosAngular ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetResBosAngular DESTINATION bin)

add_executable(GetResBosZPt util/GetResBosZPt.C)
target_link_libraries(GetResBosZPt ReadInRoot FileForEPUMP Analysis ${ROOT_LIBRARIES})
install(TARGETS GetResBosZPt DESTINATION bin)

add_executable(GetResBosPhiEta util/GetResBosPhiEta.C)
target_link_libraries(GetResBosPhiEta ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetResBosPhiEta DESTINATION bin)

add_executable(GetNonPertFitOld util/GetNonPertFitOld.C)
target_link_libraries(GetNonPertFitOld ReadInRoot FileForEPUMP Analysis ${ROOT_LIBRARIES})
install(TARGETS GetNonPertFitOld DESTINATION bin)

add_executable(GetNonPertFit util/GetNonPertFit.C)
target_link_libraries(GetNonPertFit ReadInRoot FileForEPUMP Analysis TOOL ${ROOT_LIBRARIES})
install(TARGETS GetNonPertFit DESTINATION bin)

add_executable(AFBdata util/AFBdata.C)
target_link_libraries(AFBdata FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS AFBdata DESTINATION bin)

add_executable(AFBdataNew util/AFBdataNew.C)
target_link_libraries(AFBdataNew FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS AFBdataNew DESTINATION bin)

add_executable(GetPDFUnc util/GetPDFUnc.C)
target_link_libraries(GetPDFUnc TOOL ${ROOT_LIBRARIES})
install(TARGETS GetPDFUnc DESTINATION bin)

add_executable(writeWdata util/writeWdata.C)
target_link_libraries(writeWdata FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS writeWdata DESTINATION bin)

add_executable(FillResBosRoot util/FillResBosRoot.C)
target_link_libraries(FillResBosRoot FillRoot ${ROOT_LIBRARIES})
install(TARGETS FillResBosRoot DESTINATION bin)

add_executable(CompareDataTheory util/CompareDataTheory.C)
target_link_libraries(CompareDataTheory TOOL Compare ${ROOT_LIBRARIES})
install(TARGETS CompareDataTheory DESTINATION bin)

add_executable(TryInverseMatrix util/TryInverseMatrix.C)
target_link_libraries(TryInverseMatrix TOOL ${ROOT_LIBRARIES})
install(TARGETS TryInverseMatrix DESTINATION bin)

add_executable(ReadResBosGrids util/ReadResBosGrids.C)
target_link_libraries(ReadResBosGrids ResBosGrid Analysis ${ROOT_LIBRARIES})
install(TARGETS ReadResBosGrids DESTINATION bin)

add_executable(DrawFraction util/DrawFraction.C)
target_link_libraries(DrawFraction OptimizeHelper ${ROOT_LIBRARIES})
install(TARGETS DrawFraction DESTINATION bin)

add_executable(CovAFB util/CovAFB.C)
target_link_libraries(CovAFB TOOL SpecialHist Analysis ${ROOT_LIBRARIES})
install(TARGETS CovAFB DESTINATION bin)

add_executable(tryRandom util/tryRandom.C)
target_link_libraries(tryRandom TOOL ${ROOT_LIBRARIES})
install(TARGETS tryRandom DESTINATION bin)

add_executable(UnfoldData util/UnfoldData.C)
target_link_libraries(UnfoldData FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS UnfoldData DESTINATION bin)

add_executable(tryvector util/tryvector.C)
target_link_libraries(tryvector Analysis TOOL ePump ElectroweakTheory Calculation FileForEPUMP CTEQHelper ${ROOT_LIBRARIES})
install(TARGETS tryvector DESTINATION bin)

add_executable(GetTotalLumi util/GetTotalLumi.C)
target_link_libraries(GetTotalLumi TOOL ${ROOT_LIBRARIES})
install(TARGETS GetTotalLumi DESTINATION bin)

add_executable(ExportHistograms util/ExportHistograms.C)
target_link_libraries(ExportHistograms FormatTransform Analysis ${ROOT_LIBRARIES})
install(TARGETS ExportHistograms DESTINATION bin)

add_executable(SystematicError util/SystematicError.C)
target_link_libraries(SystematicError FormatTransform Analysis ${ROOT_LIBRARIES})
install(TARGETS SystematicError DESTINATION bin)

add_executable(PDFAndQCDError util/PDFAndQCDError.C)
target_link_libraries(PDFAndQCDError FormatTransform Analysis ${ROOT_LIBRARIES})
install(TARGETS PDFAndQCDError DESTINATION bin)

add_executable(GetAFBSlope util/GetAFBSlope.C)
target_link_libraries(GetAFBSlope TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS GetAFBSlope DESTINATION bin)

add_executable(ExtractSTW util/ExtractSTW.C)
target_link_libraries(ExtractSTW Uncertainty Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractSTW DESTINATION bin)

add_executable(AFBQuarkExtraction util/AFBQuarkExtraction.C)
target_link_libraries(AFBQuarkExtraction Uncertainty Analysis Compare TOOL FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS AFBQuarkExtraction DESTINATION bin)

add_executable(AFBQuarkExtraction2D util/AFBQuarkExtraction2D.C)
target_link_libraries(AFBQuarkExtraction2D Uncertainty Analysis Compare TOOL ${ROOT_LIBRARIES})
install(TARGETS AFBQuarkExtraction2D DESTINATION bin)

add_executable(DeltaS0Fitting util/DeltaS0Fitting.C)
target_link_libraries(DeltaS0Fitting Uncertainty Analysis Compare TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS DeltaS0Fitting DESTINATION bin)

add_executable(DrawZWidthDep util/DrawZWidthDep.C)
target_link_libraries(DrawZWidthDep ElectroweakTheory ${ROOT_LIBRARIES})
install(TARGETS DrawZWidthDep DESTINATION bin)

add_executable(GetIntegral util/GetIntegral.C)
target_link_libraries(GetIntegral TOOL ${ROOT_LIBRARIES})
install(TARGETS GetIntegral DESTINATION bin)

add_executable(InverseHistXaxis util/InverseHistXaxis.C)
target_link_libraries(InverseHistXaxis TOOL ${ROOT_LIBRARIES})
install(TARGETS InverseHistXaxis DESTINATION bin)

add_executable(ApplyDilution util/ApplyDilution.C)
target_link_libraries(ApplyDilution Uncertainty Analysis Compare TOOL ${ROOT_LIBRARIES})
install(TARGETS ApplyDilution DESTINATION bin)

add_executable(DrawFunction util/DrawFunction.C)
target_link_libraries(DrawFunction TOOL ${ROOT_LIBRARIES})
install(TARGETS DrawFunction DESTINATION bin)

add_executable(GetDilution util/GetDilution.C)
target_link_libraries(GetDilution TOOL PDFHelper Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS GetDilution DESTINATION bin)

add_executable(DilutionFittingExe util/DilutionFitting.C)
target_link_libraries(DilutionFittingExe Uncertainty Analysis Compare TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS DilutionFittingExe DESTINATION bin)

add_executable(DilutionFittingMultiBin util/DilutionFittingMultiBin.C)
target_link_libraries(DilutionFittingMultiBin Uncertainty Analysis Compare TOOL TMinuitHelper SpecialHist ${ROOT_LIBRARIES})
install(TARGETS DilutionFittingMultiBin DESTINATION bin)

add_executable(NewDilutionFitting util/NewDilutionFitting.C)
target_link_libraries(NewDilutionFitting Uncertainty Analysis Compare TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFitting DESTINATION bin)

add_executable(NewDilutionFittingStw util/NewDilutionFittingStw.C)
target_link_libraries(NewDilutionFittingStw Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingStw DESTINATION bin)

add_executable(NewDilutionFittingStw4GeV util/NewDilutionFittingStw4GeV.C)
target_link_libraries(NewDilutionFittingStw4GeV Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingStw4GeV DESTINATION bin)

add_executable(NewDilutionFittingStwZY util/NewDilutionFittingStwZY.C)
target_link_libraries(NewDilutionFittingStwZY Uncertainty Analysis Compare TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingStwZY DESTINATION bin)

add_executable(NewDilutionFittingFB util/NewDilutionFittingFB.C)
target_link_libraries(NewDilutionFittingFB Uncertainty Analysis Compare TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingFB DESTINATION bin)

add_executable(NewDilutionFittingStw3D util/NewDilutionFittingStw3D.C)
target_link_libraries(NewDilutionFittingStw3D Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingStw3D DESTINATION bin)

add_executable(NewDilutionFittingStw3DLoop util/NewDilutionFittingStw3DLoop.C)
target_link_libraries(NewDilutionFittingStw3DLoop Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS NewDilutionFittingStw3DLoop DESTINATION bin)

add_executable(AFBQuarkLinear util/AFBQuarkLinear.C)
target_link_libraries(AFBQuarkLinear Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS AFBQuarkLinear DESTINATION bin)

add_executable(GetMCFMWWBoost util/GetMCFMWWBoost.C)
target_link_libraries(GetMCFMWWBoost ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetMCFMWWBoost DESTINATION bin)

add_executable(GetMCFMWWBoostPDF util/GetMCFMWWBoostPDF.C)
target_link_libraries(GetMCFMWWBoostPDF ReadInRoot Analysis Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS GetMCFMWWBoostPDF DESTINATION bin)

add_executable(DrawPDF util/DrawPDF.C)
target_link_libraries(DrawPDF TOOL PDFHelper Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS DrawPDF DESTINATION bin)

add_executable(DrawSinglePDF util/DrawSinglePDF.C)
target_link_libraries(DrawSinglePDF TOOL PDFHelper Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS DrawSinglePDF DESTINATION bin)

add_executable(MakeClass util/MakeClass.C)
target_link_libraries(MakeClass ${ROOT_LIBRARIES})
install(TARGETS MakeClass DESTINATION bin)

add_executable(GetePumpOutput util/GetePumpOutput.C)
target_link_libraries(GetePumpOutput ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetePumpOutput DESTINATION bin)

add_executable(GetPythiaWWResult util/GetPythiaWWResult.C)
target_link_libraries(GetPythiaWWResult Uncertainty Analysis Compare TOOL FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS GetPythiaWWResult DESTINATION bin)

add_executable(GetP0ECM util/GetP0ECM.C)
target_link_libraries(GetP0ECM Analysis TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS GetP0ECM DESTINATION bin)

add_executable(WWuDiagram util/WWuDiagram.C)
target_link_libraries(WWuDiagram FeynmanDiagram ${ROOT_LIBRARIES})
install(TARGETS WWuDiagram DESTINATION bin)

add_executable(GetWWBoost util/GetWWBoost.C)
target_link_libraries(GetWWBoost TOOL PDFHelper Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS GetWWBoost DESTINATION bin)

add_executable(FillSherpaWW util/FillSherpaWW.C)
target_link_libraries(FillSherpaWW FillRoot ${ROOT_LIBRARIES})
install(TARGETS FillSherpaWW DESTINATION bin)

add_executable(FittingCMSData util/FittingCMSData.C)
target_link_libraries(FittingCMSData Analysis SpecialHist TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS FittingCMSData DESTINATION bin)

add_executable(GetCMSCrossSection util/GetCMSCrossSection.C)
target_link_libraries(GetCMSCrossSection Uncertainty Analysis Compare TOOL TMinuitHelper PDFHelper FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS GetCMSCrossSection DESTINATION bin)

add_executable(GetCMSData util/GetCMSData.C)
target_link_libraries(GetCMSData ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetCMSData DESTINATION bin)

add_executable(tryroofit util/tryroofit.C)
target_link_libraries(tryroofit RooFitHelper ${ROOT_LIBRARIES})
install(TARGETS tryroofit DESTINATION bin)

add_executable(FittingWZPolarization util/FittingWZPolarization.C)
target_link_libraries(FittingWZPolarization Analysis TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS FittingWZPolarization DESTINATION bin)

add_executable(GetRAi util/GetRAi.C)
target_link_libraries(GetRAi ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetRAi DESTINATION bin)

add_executable(UpdatePDF util/UpdatePDF.C)
target_link_libraries(UpdatePDF ePumpHelper Figure TOOL ${ROOT_LIBRARIES})
install(TARGETS UpdatePDF DESTINATION bin)

add_executable(CustomPDFUnc util/CustomPDFUnc.C)
target_link_libraries(CustomPDFUnc Uncertainty ${ROOT_LIBRARIES})
install(TARGETS CustomPDFUnc DESTINATION bin)

add_executable(ExtractWMass util/ExtractWMass.C)
target_link_libraries(ExtractWMass Uncertainty FileForEPUMP PDFHelper TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractWMass DESTINATION bin)

add_executable(ExtractG2 util/ExtractG2.C)
target_link_libraries(ExtractG2 TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractG2 DESTINATION bin)

add_executable(ExtractWMass2 util/ExtractWMass2.C)
target_link_libraries(ExtractWMass2 TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractWMass2 DESTINATION bin)

add_executable(DrawWZCorrelation util/DrawWZCorrelation.C)
target_link_libraries(DrawWZCorrelation PDFHelper TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS DrawWZCorrelation DESTINATION bin)

add_executable(WMassSmear util/WMassSmear.C)
target_link_libraries(WMassSmear TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS WMassSmear DESTINATION bin)

add_executable(FittingCDFSmear util/FittingCDFSmear.C)
target_link_libraries(FittingCDFSmear Analysis SpecialHist TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS FittingCDFSmear DESTINATION bin)

add_executable(RatioWZScaleError util/RatioWZScaleError.C)
target_link_libraries(RatioWZScaleError Uncertainty TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS RatioWZScaleError DESTINATION bin)

add_executable(GetChi2 util/GetChi2.C)
target_link_libraries(GetChi2 TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS GetChi2 DESTINATION bin)

add_executable(GetPValue util/GetPValue.C)
target_link_libraries(GetPValue TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS GetPValue DESTINATION bin)

add_executable(ExtractScaleSlope util/ExtractScaleSlope.C)
target_link_libraries(ExtractScaleSlope TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractScaleSlope DESTINATION bin)

add_executable(LinearDilutionFitting util/LinearDilutionFitting.C)
target_link_libraries(LinearDilutionFitting DilutionFitting Analysis ${ROOT_LIBRARIES})
install(TARGETS LinearDilutionFitting DESTINATION bin)

add_executable(EventGenerator util/EventGenerator.C)
target_link_libraries(EventGenerator TOOL Analysis Generator ${ROOT_LIBRARIES})
install(TARGETS EventGenerator DESTINATION bin)

add_executable(GetAFBHighMassCorr util/GetAFBHighMassCorr.C)
target_link_libraries(GetAFBHighMassCorr TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS GetAFBHighMassCorr DESTINATION bin)

add_executable(ConstructP0table util/ConstructP0table.C)
target_link_libraries(ConstructP0table ePumpHelper FileForEPUMP TOOL ${ROOT_LIBRARIES})
install(TARGETS ConstructP0table DESTINATION bin)

add_executable(CustomUpdateResBosHighMass util/CustomUpdateResBosHighMass.C)
target_link_libraries(CustomUpdateResBosHighMass ePumpHelper FileForEPUMP TOOL ${ROOT_LIBRARIES})
install(TARGETS CustomUpdateResBosHighMass DESTINATION bin)

add_executable(DrawP0Correlation util/DrawP0Correlation.C)
target_link_libraries(DrawP0Correlation PDFHelper ${ROOT_LIBRARIES})
install(TARGETS DrawP0Correlation DESTINATION bin)

add_executable(ApplConvolute util/ApplConvolute.C)
target_link_libraries(ApplConvolute Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplConvolute DESTINATION bin)

if(USE_BAT)
    add_executable(templateLimitBATcombSys util/templateLimitBATcombSys.cxx)
    target_link_libraries(templateLimitBATcombSys BATHelper ePumpHelper ${ROOT_LIBRARIES})
    install(TARGETS templateLimitBATcombSys DESTINATION bin)
endif(USE_BAT)

add_executable(buildResBosZPt util/buildResBosZPt.C)
target_link_libraries(buildResBosZPt TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS buildResBosZPt DESTINATION bin)

add_executable(ReadFittingData util/ReadFittingData.C)
target_link_libraries(ReadFittingData CTEQHelper ${ROOT_LIBRARIES})
install(TARGETS ReadFittingData DESTINATION bin)

add_executable(ReadPDF util/ReadPDF.C)
target_link_libraries(ReadPDF CTEQHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS ReadPDF DESTINATION bin)

add_executable(TopTransformer util/TopTransformer.C)
target_link_libraries(TopTransformer TOOL ${ROOT_LIBRARIES})
install(TARGETS TopTransformer DESTINATION bin)

add_executable(ApplKFactor util/ApplKFactor.C)
target_link_libraries(ApplKFactor Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplKFactor DESTINATION bin)

add_executable(ParameterizeSMEFT util/ParameterizeSMEFT.C)
target_link_libraries(ParameterizeSMEFT TOOL ${ROOT_LIBRARIES})
install(TARGETS ParameterizeSMEFT DESTINATION bin)

if(USE_BAT)
    add_executable(templateLimitSMEFT util/templateLimitSMEFT.cxx)
    target_link_libraries(templateLimitSMEFT BATHelper ePumpHelper ${ROOT_LIBRARIES})
    install(TARGETS templateLimitSMEFT DESTINATION bin)

    add_executable(templateLimitSignalTest util/templateLimitSignalTest.cxx)
    target_link_libraries(templateLimitSignalTest BATHelper ePumpHelper ${ROOT_LIBRARIES})
    install(TARGETS templateLimitSignalTest DESTINATION bin)
endif(USE_BAT)

add_executable(FittingSMEFT util/FittingSMEFT.C)
target_link_libraries(FittingSMEFT TOOL TMinuitHelper ePumpHelper ${ROOT_LIBRARIES})
install(TARGETS FittingSMEFT DESTINATION bin)

add_executable(ApplAFB util/ApplAFB.C)
target_link_libraries(ApplAFB Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplAFB DESTINATION bin)

add_executable(DrawL2Sensitivity util/DrawL2Sensitivity.C)
target_link_libraries(DrawL2Sensitivity CTEQHelper ${ROOT_LIBRARIES})
install(TARGETS DrawL2Sensitivity DESTINATION bin)

if(USE_BAT)
    add_executable(templateLimitFB util/templateLimitFB.cxx)
    target_link_libraries(templateLimitFB BATHelper ePumpHelper ${ROOT_LIBRARIES})
    install(TARGETS templateLimitFB DESTINATION bin)

    add_executable(templateLimitFBnoPenalty util/templateLimitFBnoPenalty.cxx)
    target_link_libraries(templateLimitFBnoPenalty BATHelper ePumpHelper ${ROOT_LIBRARIES})
    install(TARGETS templateLimitFBnoPenalty DESTINATION bin)
endif(USE_BAT)

add_executable(ApplWZBoost util/ApplWZBoost.C)
target_link_libraries(ApplWZBoost Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplWZBoost DESTINATION bin)

add_executable(ExtractWMassbyJacoAsym util/ExtractWMassbyJacoAsym.C)
target_link_libraries(ExtractWMassbyJacoAsym Uncertainty FileForEPUMP PDFHelper TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS ExtractWMassbyJacoAsym DESTINATION bin)

add_executable(CustomPartonCorr util/CustomPartonCorr.C)
target_link_libraries(CustomPartonCorr PDFHelper ${ROOT_LIBRARIES})
install(TARGETS CustomPartonCorr DESTINATION bin)

add_executable(InterpolateN3LO util/InterpolateN3LO.C)
target_link_libraries(InterpolateN3LO TOOL ResBosGrid ${ROOT_LIBRARIES})
install(TARGETS InterpolateN3LO DESTINATION bin)

add_executable(JacoAsymCorrelation util/JacoAsymCorrelation.C)
target_link_libraries(JacoAsymCorrelation Uncertainty FileForEPUMP PDFHelper TOOL Analysis ${ROOT_LIBRARIES})
install(TARGETS JacoAsymCorrelation DESTINATION bin)

add_executable(OptimizePDF util/OptimizePDF.C)
target_link_libraries(OptimizePDF ePumpHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS OptimizePDF DESTINATION bin)

add_executable(Random util/Random.C)
target_link_libraries(Random ${ROOT_LIBRARIES})
install(TARGETS Random DESTINATION bin)

add_executable(GetNNLOZPt util/GetNNLOZPt.C)
target_link_libraries(GetNNLOZPt ReadInRoot Analysis ${ROOT_LIBRARIES})
install(TARGETS GetNNLOZPt DESTINATION bin)

add_executable(CorrelationEllipse util/CorrelationEllipse.C)
target_link_libraries(CorrelationEllipse PDFHelper ${ROOT_LIBRARIES})
install(TARGETS CorrelationEllipse DESTINATION bin)

add_executable(Training util/Training.C)
target_link_libraries(Training TMVAInterface ${ROOT_LIBRARIES})
install(TARGETS Training DESTINATION bin)

add_executable(TMVAReader util/TMVAReader.C)
target_link_libraries(TMVAReader TMVAInterface TOOL TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS TMVAReader DESTINATION bin)

add_executable(DrawPDFLumi util/DrawPDFLumi.C)
target_link_libraries(DrawPDFLumi PDFHelper ${ROOT_LIBRARIES})
install(TARGETS DrawPDFLumi DESTINATION bin)

add_executable(P0Correlation util/P0Correlation.C)
target_link_libraries(P0Correlation TOOL PDFHelper ${ROOT_LIBRARIES})
install(TARGETS P0Correlation DESTINATION bin)

add_executable(ApplWLeptonPt util/ApplWLeptonPt.C)
target_link_libraries(ApplWLeptonPt Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplWLeptonPt DESTINATION bin)

add_executable(DrawPDFEigen util/DrawPDFEigen.C)
target_link_libraries(DrawPDFEigen TOOL PDFHelper Uncertainty FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS DrawPDFEigen DESTINATION bin)

add_executable(ApplCT18DY util/ApplCT18DY.C)
target_link_libraries(ApplCT18DY Calculation ReadInRoot ${ROOT_LIBRARIES})
install(TARGETS ApplCT18DY DESTINATION bin)

add_executable(CT18DYKFactor util/CT18DYKFactor.C)
target_link_libraries(CT18DYKFactor Analysis ReadInRoot Calculation TOOL ${ROOT_LIBRARIES})
install(TARGETS CT18DYKFactor DESTINATION bin)

add_executable(FitStrange util/FitStrange.C)
target_link_libraries(FitStrange DilutionFitting Analysis ${ROOT_LIBRARIES})
install(TARGETS FitStrange DESTINATION bin)

add_executable(FlavorSearchFit util/FlavorSearchFit.C)
target_link_libraries(FlavorSearchFit DilutionFitting Analysis ${ROOT_LIBRARIES})
install(TARGETS FlavorSearchFit DESTINATION bin)

add_executable(GetLMScan util/GetLMScan.C)
target_link_libraries(GetLMScan CTEQHelper ${ROOT_LIBRARIES})
install(TARGETS GetLMScan DESTINATION bin)

add_executable(OutputPDF util/OutputPDF.C)
target_link_libraries(OutputPDF CTEQHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS OutputPDF DESTINATION bin)

add_executable(ThreadApplConvolute util/ThreadApplConvolute.C)
target_link_libraries(ThreadApplConvolute CTEQHelper Calculation ${ROOT_LIBRARIES})
install(TARGETS ThreadApplConvolute DESTINATION bin)

add_executable(GenerateCT18 util/GenerateCT18.C)
target_link_libraries(GenerateCT18 CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS GenerateCT18 DESTINATION bin)

add_executable(FastNLOConvolute util/FastNLOConvolute.C)
target_link_libraries(FastNLOConvolute Calculation ${ROOT_LIBRARIES})
install(TARGETS FastNLOConvolute DESTINATION bin)

add_executable(FixedTargetKFactor util/FixedTargetKFactor.C)
target_link_libraries(FixedTargetKFactor ${ROOT_LIBRARIES})
install(TARGETS FixedTargetKFactor DESTINATION bin)

add_executable(SimplePlot util/SimplePlot.C)
target_link_libraries(SimplePlot Figure ${ROOT_LIBRARIES})
install(TARGETS SimplePlot DESTINATION bin)

add_executable(PDFFit util/PDFFit.C)
target_link_libraries(PDFFit CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS PDFFit DESTINATION bin)

add_executable(PDFFit_Minuit2 util/PDFFit_Minuit2.C)
target_link_libraries(PDFFit_Minuit2 CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS PDFFit_Minuit2 DESTINATION bin)

add_executable(PDFFit_Minimizer util/PDFFit_Minimizer.C)
target_link_libraries(PDFFit_Minimizer CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS PDFFit_Minimizer DESTINATION bin)

if(USE_BAT)
    add_executable(PDFFit_BAT util/PDFFit_BAT.C)
    target_link_libraries(PDFFit_BAT CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
    install(TARGETS PDFFit_BAT DESTINATION bin)
endif(USE_BAT)

add_executable(PDFLMScan util/PDFLMScan.C)
target_link_libraries(PDFLMScan CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS PDFLMScan DESTINATION bin)

add_executable(AlphaSLMScan util/AlphaSLMScan.C)
target_link_libraries(AlphaSLMScan CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS AlphaSLMScan DESTINATION bin)

add_executable(PDFEVSet util/PDFEVSet.C)
target_link_libraries(PDFEVSet CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS PDFEVSet DESTINATION bin)

add_executable(CheckDIS util/CheckDIS.C)
target_link_libraries(CheckDIS CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS CheckDIS DESTINATION bin)

add_executable(TryYAML util/TryYAML.C)
target_link_libraries(TryYAML Calculation ${yaml-cpp_LIBRARIES} ${ROOT_LIBRARIES})
install(TARGETS TryYAML DESTINATION bin)

add_executable(RewriteTree util/RewriteTree.C)
target_link_libraries(RewriteTree ${ROOT_LIBRARIES})
install(TARGETS RewriteTree DESTINATION bin)

add_executable(ReloopHMDYFake util/ReloopHMDYFake.C)
target_link_libraries(ReloopHMDYFake Eigen3::Eigen ${ROOT_LIBRARIES})
install(TARGETS ReloopHMDYFake DESTINATION bin)

add_executable(ReloopHMDYFakeMuon util/ReloopHMDYFakeMuon.C)
target_link_libraries(ReloopHMDYFakeMuon Eigen3::Eigen ${ROOT_LIBRARIES})
install(TARGETS ReloopHMDYFakeMuon DESTINATION bin)

add_executable(HMDYSys util/HMDYSys.C)
target_link_libraries(HMDYSys Analysis SpecialHist TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS HMDYSys DESTINATION bin)

add_executable(TestMinuit2 util/TestMinuit2.C)
target_link_libraries(TestMinuit2 Analysis SpecialHist TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS TestMinuit2 DESTINATION bin)

add_executable(Readwtrans util/Readwtrans.C)
target_link_libraries(Readwtrans CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS Readwtrans DESTINATION bin)

add_executable(ReadEV util/ReadEV.C)
target_link_libraries(ReadEV CTEQHelper PDFHelper Calculation TMinuitHelper ${ROOT_LIBRARIES})
install(TARGETS ReadEV DESTINATION bin)

add_executable(TryAdaptiveInt util/TryAdaptiveInt.C)
target_link_libraries(TryAdaptiveInt CTEQHelper PDFHelper Calculation TMinuitHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS TryAdaptiveInt DESTINATION bin)

add_executable(CheckSumRule util/CheckSumRule.C)
target_link_libraries(CheckSumRule CTEQHelper PDFHelper ${ROOT_LIBRARIES})
install(TARGETS CheckSumRule DESTINATION bin)

add_executable(TryFantomas util/TryFantomas.C)
target_link_libraries(TryFantomas CTEQHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS TryFantomas DESTINATION bin)

add_executable(ProducePDF util/ProducePDF.C)
target_link_libraries(ProducePDF CTEQHelper Calculation TOOL ${ROOT_LIBRARIES})
install(TARGETS ProducePDF DESTINATION bin)

add_executable(ApplAFBRapidity util/ApplAFBRapidity.C)
target_link_libraries(ApplAFBRapidity Calculation ${ROOT_LIBRARIES})
install(TARGETS ApplAFBRapidity DESTINATION bin)

add_executable(OrganizePDFHist util/OrganizePDFHist.C)
target_link_libraries(OrganizePDFHist ${ROOT_LIBRARIES})
install(TARGETS OrganizePDFHist DESTINATION bin)

add_executable(OptimizeBinning util/OptimizeBinning.C)
target_link_libraries(OptimizeBinning ePumpHelper Figure ${ROOT_LIBRARIES})
install(TARGETS OptimizeBinning DESTINATION bin)

add_executable(MakePDFCluster util/MakePDFCluster.C)
target_link_libraries(MakePDFCluster CTEQHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS MakePDFCluster DESTINATION bin)

add_executable(p2lFullSet util/p2lFullSet.C)
target_link_libraries(p2lFullSet CTEQHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS p2lFullSet DESTINATION bin)

add_executable(l2pFullSet util/l2pFullSet.C)
target_link_libraries(l2pFullSet CTEQHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS l2pFullSet DESTINATION bin)

add_executable(OperateCTEQPDF util/OperateCTEQPDF.C)
target_link_libraries(OperateCTEQPDF CTEQHelper TOOL ${ROOT_LIBRARIES})
install(TARGETS OperateCTEQPDF DESTINATION bin)

add_executable(NewDrellYanKFactor util/NewDrellYanKFactor.C)
target_link_libraries(NewDrellYanKFactor TOOL ${ROOT_LIBRARIES})
install(TARGETS NewDrellYanKFactor DESTINATION bin)

if(USE_PINEAPPL)
    add_executable(PineAPPLConvolute util/PineAPPLConvolute.C)
    target_link_libraries(PineAPPLConvolute Calculation TOOL ${ROOT_LIBRARIES})
    install(TARGETS PineAPPLConvolute DESTINATION bin)
endif(USE_PINEAPPL)

add_executable(ConvertCTfitinp util/ConvertCTfitinp.C)
target_link_libraries(ConvertCTfitinp ${ROOT_LIBRARIES})
install(TARGETS ConvertCTfitinp DESTINATION bin)

add_executable(HQZM util/HQZM.C)
target_link_libraries(HQZM CTEQHelper Calculation ${ROOT_LIBRARIES})
install(TARGETS HQZM DESTINATION bin)

add_executable(WriteFilesSMEFT util/WriteFilesSMEFT.C)
target_link_libraries(WriteFilesSMEFT FileForEPUMP ${ROOT_LIBRARIES})
install(TARGETS WriteFilesSMEFT DESTINATION bin)
