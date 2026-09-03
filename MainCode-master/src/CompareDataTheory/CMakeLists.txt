include_directories(${CMAKE_SOURCE_DIR}/include/CompareDataTheory)

aux_source_directory(. DIR_COMPARE_SRC)
add_library(Compare SHARED ${DIR_COMPARE_SRC})
target_link_libraries(Compare TOOL Uncertainty)

install(TARGETS Compare
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/CompareDataTheory/*.h)
#install(FILES ${loop_headers} DESTINATION include/CompareDataTheory)

