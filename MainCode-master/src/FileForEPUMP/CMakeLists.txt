include_directories(${CMAKE_SOURCE_DIR}/include/FileForEPUMP)

aux_source_directory(. DIR_FILEEPUMP_SRC)
add_library(FileForEPUMP SHARED ${DIR_FILEEPUMP_SRC})
target_link_libraries(FileForEPUMP TOOL Uncertainty)

install(TARGETS FileForEPUMP
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/FileForEPUMP/*.h)
#install(FILES ${loop_headers} DESTINATION include/FileForEPUMP)

