include_directories(${CMAKE_SOURCE_DIR}/include/BATHelper)

aux_source_directory(. DIR_BATHELPER_SRC)
add_library(BATHelper SHARED ${DIR_BATHELPER_SRC})
target_link_libraries(BATHelper TOOL)

install(TARGETS BATHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/BATHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/BATHelper)

