include_directories(${CMAKE_SOURCE_DIR}/include/Figure)

aux_source_directory(. DIR_FIGURE_SRC)
add_library(Figure SHARED ${DIR_FIGURE_SRC})
target_link_libraries(Figure ${ROOT_LIBRARIES})

install(TARGETS Figure
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Figure/*.h)
#install(FILES ${loop_headers} DESTINATION include/Figure)

