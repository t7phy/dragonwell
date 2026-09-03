if(USE_ROOFIT)
    add_definitions(-DUSE_ROOFIT)
endif(USE_ROOFIT)

include_directories(${CMAKE_SOURCE_DIR}/include/RooFitHelper)

aux_source_directory(. DIR_ROOFIT_SRC)
add_library(RooFitHelper SHARED ${DIR_ROOFIT_SRC})
target_link_libraries(RooFitHelper ${ROOT_LIBRARIES})

install(TARGETS RooFitHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/RooFitHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/RooFitHelper)
