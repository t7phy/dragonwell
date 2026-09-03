include_directories(${CMAKE_SOURCE_DIR}/include/Fantomas)

aux_source_directory(. DIR_FANTOMAS_SRC)
add_library(Fantomas SHARED ${DIR_FANTOMAS_SRC})

install(TARGETS Fantomas
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Fantomas/*.h)
#install(FILES ${loop_headers} DESTINATION include/Fantomas)

