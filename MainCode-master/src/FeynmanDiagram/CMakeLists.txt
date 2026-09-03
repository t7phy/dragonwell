include_directories(${CMAKE_SOURCE_DIR}/include/FeynmanDiagram)

aux_source_directory(. DIR_FD_SRC)
add_library(FeynmanDiagram SHARED ${DIR_FD_SRC})

install(TARGETS FeynmanDiagram
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/FeynmanDiagram/*.h)
#install(FILES ${loop_headers} DESTINATION include/FeynmanDiagram)
