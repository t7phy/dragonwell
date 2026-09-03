include_directories(${CMAKE_SOURCE_DIR}/include/Generator)

aux_source_directory(. DIR_GENERATOR_SRC)
add_library(Generator SHARED ${DIR_GENERATOR_SRC})
target_link_libraries(Generator TOOL ElectroweakTheory)

install(TARGETS Generator
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Generator/*.h)
#install(FILES ${loop_headers} DESTINATION include/Generator)

