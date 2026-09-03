
if(USE_TMVA)
    add_definitions(-DUSE_TMVA)
endif(USE_TMVA)

include_directories(${CMAKE_SOURCE_DIR}/include/Analysis)

aux_source_directory(. DIR_ANALYSIS_SRC)
aux_source_directory(../CustomVersion DIR_CUSTOM_SRC)
aux_source_directory(../WZPolarization DIR_WZPOL_SRC)
aux_source_directory(../Wasymmetry DIR_WASYM_SRC)
aux_source_directory(../QBH DIR_QBH_SRC)
aux_source_directory(../HighMassDY DIR_HMDY_SRC)
aux_source_directory(../ZPrime DIR_ZPrime_SRC)


add_library(Analysis SHARED ${DIR_ANALYSIS_SRC} ${DIR_CUSTOM_SRC} ${DIR_WZPOL_SRC} ${DIR_WASYM_SRC} ${DIR_QBH_SRC} ${DIR_HMDY_SRC} ${DIR_ZPrime_SRC})
target_link_libraries(Analysis TOOL Dictionary PDFHelper SpecialHist TMinuitHelper ReadInRoot Eigen3::Eigen ${ROOT_LIBRARIES})

install(TARGETS Analysis
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Analysis/*.h)
#install(FILES ${loop_headers} DESTINATION include/Analysis)
