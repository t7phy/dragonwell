include_directories(${CMAKE_SOURCE_DIR}/include/Calibration)

aux_source_directory(. DIR_CALIBRATION_SRC)
add_library(Calibration SHARED ${DIR_CALIBRATION_SRC})

install(TARGETS Calibration
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Calibration/*.h)
install(FILES ${loop_headers} DESTINATION include/Calibration)

