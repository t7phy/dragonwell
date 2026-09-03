include_directories(${CMAKE_SOURCE_DIR}/include/Uncertainty)

aux_source_directory(. DIR_UNC_SRC)
add_library(Uncertainty SHARED ${DIR_UNC_SRC})
target_link_libraries(Uncertainty TOOL)

install(TARGETS Uncertainty
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Uncertainty/*.h)
#install(FILES ${loop_headers} DESTINATION include/Uncertainty)

