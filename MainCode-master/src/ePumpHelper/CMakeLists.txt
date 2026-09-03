#include_directories(${CMAKE_SOURCE_DIR}/include/ePumpHelper)

aux_source_directory(. DIR_EPUMPHELPER_SRC)

add_library(ePumpHelper SHARED ${DIR_EPUMPHELPER_SRC})

get_target_property(EIGEN_INCLUDE_DIR Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(ePumpHelper PRIVATE ${CMAKE_SOURCE_DIR}/include/ePumpHelper)
target_include_directories(ePumpHelper PUBLIC ${EIGEN_INCLUDE_DIR})

target_link_libraries(ePumpHelper ePump CTEQHelper Figure Eigen3::Eigen)

if(USE_SWIG)
    set(CMAKE_SWIG_FLAGS -c++ -std=c++17)
    set_source_files_properties(PyePump.i PROPERTIES CPLUSPLUS ON OUTFILE_DIR ${CMAKE_CURRENT_BINARY_DIR})
    swig_add_library(PyePump TYPE MODULE LANGUAGE python SOURCES PyePump.i PyePump.C)

    swig_link_libraries(PyePump ePumpHelper
                                ePump
                                CTEQHelper
                                Figure
                                Eigen3::Eigen
                                stdc++fs
                                ${ROOT_LIBRARIES}
                                ROOT::Minuit2)
else(USE_SWIG)
    if(USE_PYTHON)
        find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
        add_library(_PyePump MODULE ${CMAKE_CURRENT_SOURCE_DIR}/PythonExt/PyePumpPYTHON_wrap.cxx)
        target_include_directories(_PyePump PRIVATE ${Python3_INCLUDE_DIRS})
        target_link_libraries(_PyePump ePumpHelper ${Python3_LIBRARIES})
        set_target_properties(_PyePump PROPERTIES PREFIX "")
    endif(USE_PYTHON)
endif(USE_SWIG)

install(TARGETS ePumpHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

if(USE_SWIG)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PyePump.py DESTINATION bin)
else(USE_SWIG)
    if(USE_PYTHON)
        install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/PythonExt/PyePump.py DESTINATION bin)
        install(TARGETS _PyePump
                ARCHIVE DESTINATION lib
                LIBRARY DESTINATION bin
                RUNTIME DESTINATION bin)
    endif(USE_PYTHON)
endif(USE_SWIG)



#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/ePumpHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/ePumpHelper)

