include_directories(${CMAKE_SOURCE_DIR}/include/ReadInRoot)

aux_source_directory(. DIR_READIN_SRC)
add_library(ReadInRoot SHARED ${DIR_READIN_SRC})
target_link_libraries(ReadInRoot TOOL FileForEPUMP)

install(TARGETS ReadInRoot
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/ReadInRoot/*.h)
#install(FILES ${loop_headers} DESTINATION include/ReadInRoot)

