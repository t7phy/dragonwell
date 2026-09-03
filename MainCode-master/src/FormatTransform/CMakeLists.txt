include_directories(${CMAKE_SOURCE_DIR}/include/FormatTransform)

aux_source_directory(. DIR_FORMAT_SRC)
add_library(FormatTransform SHARED ${DIR_FORMAT_SRC})
target_link_libraries(FormatTransform Analysis TOOL Uncertainty)

install(TARGETS FormatTransform
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/FormatTransform/*.h)
#install(FILES ${loop_headers} DESTINATION include/FormatTransform)

