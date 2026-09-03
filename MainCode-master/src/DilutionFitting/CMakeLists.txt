include_directories(${CMAKE_SOURCE_DIR}/include/DilutionFitting)

aux_source_directory(. DIR_DILUTION_SRC)
add_library(DilutionFitting SHARED ${DIR_DILUTION_SRC})
target_link_libraries(DilutionFitting TOOL ElectroweakTheory Uncertainty FileForEPUMP TMinuitHelper ePumpHelper CTEQHelper)

install(TARGETS DilutionFitting
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/DilutionFitting/*.h)
#install(FILES ${loop_headers} DESTINATION include/DilutionFitting)

