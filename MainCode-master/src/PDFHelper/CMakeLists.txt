include_directories(${CMAKE_SOURCE_DIR}/include/PDFHelper)

aux_source_directory(. DIR_PDF_SRC)
add_library(PDFHelper SHARED ${DIR_PDF_SRC})
target_link_libraries(PDFHelper TOOL ElectroweakTheory Uncertainty FileForEPUMP CTEQHelper Figure)

install(TARGETS PDFHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/PDFHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/PDFHelper)

