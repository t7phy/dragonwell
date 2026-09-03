include_directories(${CMAKE_SOURCE_DIR}/include/TMinuitHelper)

aux_source_directory(. DIR_TMINUIT_SRC)
add_library(TMinuitHelper SHARED ${DIR_TMINUIT_SRC})
target_link_libraries(TMinuitHelper ${ROOT_LIBRARIES})

install(TARGETS TMinuitHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/TMinuitHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/TMinuitHelper)

