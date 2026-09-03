cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0074 NEW)
project(loopMC)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

find_package(ROOT)
set(ROOT_DIR $ENV{ROOTSYS}/cmake)
set(ROOT_INCLUDE_DIRS $ENV{ROOTSYS}/include)

include_directories(${ROOT_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)

set(ROOT_LIBRARIES
"$ENV{ROOTSYS}/lib/libCore.so"
"$ENV{ROOTSYS}/lib/libRIO.so"
"$ENV{ROOTSYS}/lib/libNet.so"
"$ENV{ROOTSYS}/lib/libHistFactory.so"
"$ENV{ROOTSYS}/lib/libHistPainter.so"
"$ENV{ROOTSYS}/lib/libHist.so"
"$ENV{ROOTSYS}/lib/libGraf3d.so"
"$ENV{ROOTSYS}/lib/libGraf.so"
"$ENV{ROOTSYS}/lib/libGraf3d.so"
"$ENV{ROOTSYS}/lib/libGpad.so"
"$ENV{ROOTSYS}/lib/libTreePlayer.so"
"$ENV{ROOTSYS}/lib/libTree.so"
"$ENV{ROOTSYS}/lib/libTreeViewer.so"
"$ENV{ROOTSYS}/lib/libRint.so"
"$ENV{ROOTSYS}/lib/libPostscript.so"
"$ENV{ROOTSYS}/lib/libMatrix.so"
"$ENV{ROOTSYS}/lib/libPhysics.so"
"$ENV{ROOTSYS}/lib/libMathCore.so"
"$ENV{ROOTSYS}/lib/libThread.so"
"$ENV{ROOTSYS}/lib/libMultiProc.so"
"$ENV{ROOTSYS}/lib/libMinuit.so"
"$ENV{ROOTSYS}/lib/libmap2Dict.so"
"$ENV{ROOTSYS}/lib/libmapDict.so"
"$ENV{ROOTSYS}/lib/libmultimap2Dict.so"
"$ENV{ROOTSYS}/lib/libmultimapDict.so"
"$ENV{ROOTSYS}/lib/libmultisetDict.so"
"$ENV{ROOTSYS}/lib/libRooFitCore.so"
"$ENV{ROOTSYS}/lib/libRooFit.so"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

option(USE_LHAPDF ON)
option(USE_LWTNN ON)
option(USE_TMVA ON)
option(USE_ROOFIT ON)
option(USE_APPLGRID ON)
option(USE_BAT ON)
option(USE_ROOUNFOLD ON)
option(USE_HOPPET ON)
option(USE_FNLO ON)
option(USE_MINUIT2 ON)
option(USE_YAML ON)

#change the option here
set(USE_LHAPDF ON)
set(USE_LWTNN OFF)
set(USE_TMVA OFF)
set(USE_ROOFIT OFF)
set(USE_APPLGRID OFF)
set(USE_BAT OFF)
set(USE_ROOUNFOLD OFF)
set(USE_HOPPET OFF)
set(USE_FNLO OFF)
set(USE_MINUIT2 OFF)
set(USE_YAML OFF)

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
    set(yaml-cpp_INCLUDE_DIRS $ENV{YAML_ROOT_DIR}/include)
    set(yaml-cpp_LIBRARIES $ENV{YAML_ROOT_DIR}/lib64/libyaml-cpp.so)
    set(yaml-cpp_LIBRARIES "${yaml-cpp_LIBRARIES};$ENV{YAML_ROOT_DIR}/lib64/libyaml-cpp.so.0.8")
    set(yaml-cpp_LIBRARIES "${yaml-cpp_LIBRARIES};$ENV{YAML_ROOT_DIR}/lib64/libyaml-cpp.so.0.8.0")
    include_directories(${yaml-cpp_INCLUDE_DIRS})
endif(USE_YAML)

#HOPPET
if(USE_HOPPET)
    add_definitions(-DUSE_HOPPET)
    set(Hoppet_ROOT $ENV{Hoppet_ROOT_DIR})
    set(Hoppet_INCLUDE_DIRS $ENV{Hoppet_ROOT_DIR}/include)
    include_directories(${Hoppet_INCLUDE_DIRS})
endif(USE_HOPPET)

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

include_directories(include)
add_subdirectory(src)

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
    set(ROOT_LIBRARIES "${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFitMore.so")
endif(USE_ROOFIT)

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


