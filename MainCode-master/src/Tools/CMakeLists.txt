#include_directories(${CMAKE_SOURCE_DIR}/include/Figure)
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_ROOT_DIR}/CMake/FindLHAPDF.cmake)
#include(${CMAKE_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if(USE_LHAPDF)
    set(LHAPDF_ROOT $ENV{LHAPDF_ROOT_DIR})
    set(LHAPDF_INCLUDE_DIRS $ENV{LHAPDF_ROOT_DIR}/include)
    set(LHAPDF_LIBRARIES $ENV{LHAPDF_ROOT_DIR}/lib)
endif(USE_LHAPDF)

if(USE_APPLGRID)
    set(APPLGRID_ROOT $ENV{APPLGRID_ROOT_DIR})
    set(APPLGRID_INCLUDE_DIRS $ENV{APPLGRID_ROOT_DIR}/include)
    set(APPLGRID_LIBRARIES $ENV{APPLGRID_ROOT_DIR}/lib)
endif(USE_APPLGRID)

if(USE_BAT)
    set(BAT_ROOT $ENV{BAT_ROOT_DIR})
    set(BAT_INCLUDE_DIRS $ENV{BAT_ROOT_DIR}/include)
    set(BAT_LIBRARIES $ENV{BAT_ROOT_DIR}/lib)
endif(USE_BAT)

if(USE_ROOUNFOLD)
    find_package(RooUnfold)
    set(RooUnfold_ROOT $ENV{ROOUNFOLD_ROOT_DIR})
    set(RooUnfold_INCLUDE_DIRS $ENV{ROOUNFOLD_ROOT_DIR}/include)
    set(RooUnfold_LIBRARIES $ENV{ROOUNFOLD_ROOT_DIR}/lib/libRooUnfold.so)
    include_directories(${RooUnfold_INCLUDE_DIRS})
endif(USE_ROOUNFOLD)

if(USE_FNLO)
    set(FASTNLO_ROOT $ENV{FASTNLO_ROOT_DIR})
    set(FASTNLO_INCLUDE_DIRS $ENV{FASTNLO_ROOT_DIR}/include)
    set(FASTNLO_LIBRARIES $ENV{FASTNLO_ROOT_DIR}/lib)
endif(USE_FNLO)

if(USE_LHAPDF)
    find_package(LHAPDF REQUIRED)
endif(USE_LHAPDF)

if(USE_APPLGRID)
    find_package(APPLGRID REQUIRED)
endif(USE_APPLGRID)

if(USE_BAT)
    find_package(BAT REQUIRED)
endif(USE_BAT)

if(USE_FNLO)
    find_package(FASTNLO REQUIRED)
endif(USE_FNLO)


aux_source_directory(. DIR_TOOL_SRC)
add_library(TOOL SHARED ${DIR_TOOL_SRC})
target_link_libraries(TOOL ElectroweakTheory
                           ${LHAPDF_LIBRARIES}
                           ${LWTNN_LIBRARIES}
                           ${APPLGRID_LIBRARIES}
                           ${BAT_LIBRARIES}
                           ${RooUnfold_LIBRARIES}
                           ${FASTNLO_LIBRARIES}
                           ${ROOT_LIBRARIES})

install(TARGETS TOOL
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB tools_headers ${CMAKE_SOURCE_DIR}/include/Tools/*.h)
#install(FILES ${tools_headers} DESTINATION include/Tools)

