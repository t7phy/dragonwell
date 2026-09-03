include_directories(${CMAKE_SOURCE_DIR}/include/ReadResBosGrid)

aux_source_directory(. DIR_RESBOSGRID_SRC)
add_library(ResBosGrid SHARED ${DIR_RESBOSGRID_SRC})
target_link_libraries(ResBosGrid TOOL)

install(TARGETS ResBosGrid
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/ReadResBosGrid/*.h)
#install(FILES ${loop_headers} DESTINATION include/ReadResBosGrid)

