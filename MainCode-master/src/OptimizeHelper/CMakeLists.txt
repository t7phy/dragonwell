include_directories(${CMAKE_SOURCE_DIR}/include/OptimizeHelper)

aux_source_directory(. DIR_OPTIMIZE_SRC)
add_library(OptimizeHelper SHARED ${DIR_OPTIMIZE_SRC})

install(TARGETS OptimizeHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/OptimizeHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/OptimizeHelper)

