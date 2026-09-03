if(USE_TMVA)
    add_definitions(-DUSE_TMVA)
endif(USE_TMVA)

include_directories(${CMAKE_SOURCE_DIR}/include/TMVAInterface)

aux_source_directory(. DIR_TMVAINTERFACE_SRC)
add_library(TMVAInterface SHARED ${DIR_TMVAINTERFACE_SRC})
target_link_libraries(TMVAInterface TOOL)

install(TARGETS TMVAInterface
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/TMVAInterface/*.h)
#install(FILES ${loop_headers} DESTINATION include/TMVAInterface)

