include_directories(${CMAKE_SOURCE_DIR}/include/ePump)

aux_source_directory(. DIR_EPUMP_SRC)
add_library(ePump SHARED ${DIR_EPUMP_SRC})
target_link_libraries(ePump TOOL Eigen3::Eigen)

install(TARGETS ePump
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/ePump/*.h)
#install(FILES ${loop_headers} DESTINATION include/ePump)

