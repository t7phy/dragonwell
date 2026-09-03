if(USE_TMVA)
    add_definitions(-DUSE_TMVA)
endif(USE_TMVA)
include_directories(${CMAKE_SOURCE_DIR}/include/WZPolarization)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/WZPolarization/*.h)
#install(FILES ${loop_headers} DESTINATION include/WZPolarization)

