include_directories(${CMAKE_SOURCE_DIR}/include/Calculation)

aux_source_directory(. DIR_APPL_SRC)

if(NOT USE_BAT)
    list(REMOVE_ITEM DIR_APPL_SRC ./GlobalFitting_BAT.C)
endif(NOT USE_BAT)

if(USE_JSON)
    add_definitions(-DUSE_JSON)
endif(USE_JSON)

add_library(Calculation SHARED ${DIR_APPL_SRC})

if(USE_BAT)
    target_link_libraries(Calculation TOOL 
                                      Uncertainty
                                      FileForEPUMP
                                      CTEQHelper
                                      TMinuitHelper
                                      Eigen3::Eigen
                                      Integration
                                      ${yaml-cpp_LIBRARIES}
                                      stdc++fs
                                      ${BAT_LIBRARIES})
else(USE_BAT)
    target_link_libraries(Calculation TOOL
                                      Uncertainty
                                      FileForEPUMP
                                      CTEQHelper
                                      TMinuitHelper
                                      Eigen3::Eigen
                                      Integration
                                      ${yaml-cpp_LIBRARIES}
                                      stdc++fs)
endif(USE_BAT)

if(USE_PINEAPPL)
    target_link_libraries(Calculation PkgConfig::PINEAPPL)
endif(USE_PINEAPPL)

if(USE_SWIG)
    set(CMAKE_SWIG_FLAGS -c++ -std=c++17)
    set_source_files_properties(PyGlobalFitting.i PROPERTIES CPLUSPLUS ON OUTFILE_DIR ${CMAKE_CURRENT_BINARY_DIR})
    swig_add_library(PyGlobalFitting TYPE MODULE LANGUAGE python SOURCES PyGlobalFitting.i PyGlobalFitting.C)

    if(USE_PINEAPPL)
        swig_link_libraries(PyGlobalFitting Calculation
                                            TOOL
                                            Uncertainty
                                            FileForEPUMP
                                            CTEQHelper
                                            TMinuitHelper
                                            Eigen3::Eigen
                                            Integration
                                            ${yaml-cpp_LIBRARIES}
                                            stdc++fs
                                            ${ROOT_LIBRARIES}
                                            ROOT::Minuit2
                                            PkgConfig::PINEAPPL)
    else(USE_PINEAPPL)
        swig_link_libraries(PyGlobalFitting Calculation
                                            TOOL
                                            Uncertainty
                                            FileForEPUMP
                                            CTEQHelper
                                            TMinuitHelper
                                            Eigen3::Eigen
                                            Integration
                                            ${yaml-cpp_LIBRARIES}
                                            stdc++fs
                                            ${ROOT_LIBRARIES}
                                            ROOT::Minuit2)
    endif(USE_PINEAPPL)

endif(USE_SWIG)

install(TARGETS Calculation
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

if(USE_SWIG)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/PyGlobalFitting.py DESTINATION bin)
endif(USE_SWIG)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Calculation/*.h)
#install(FILES ${loop_headers} DESTINATION include/Calculation)

