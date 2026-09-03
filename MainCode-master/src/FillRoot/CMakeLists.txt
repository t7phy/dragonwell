include_directories(${CMAKE_SOURCE_DIR}/include/FillRoot)

aux_source_directory(. DIR_FILLROOT_SRC)
add_library(FillRoot SHARED ${DIR_FILLROOT_SRC})

install(TARGETS FillRoot
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/FillRoot/*.h)
#install(FILES ${loop_headers} DESTINATION include/FillRoot)

