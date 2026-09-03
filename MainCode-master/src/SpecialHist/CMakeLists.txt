include_directories(${CMAKE_SOURCE_DIR}/include/SpecialHist)

aux_source_directory(. DIR_HIST_SRC)
add_library(SpecialHist SHARED ${DIR_HIST_SRC})
target_link_libraries(SpecialHist TOOL)

install(TARGETS SpecialHist
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/SpecialHist/*.h)
#install(FILES ${loop_headers} DESTINATION include/SpecialHist)

