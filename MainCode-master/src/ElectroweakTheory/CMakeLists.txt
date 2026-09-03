include_directories(${CMAKE_SOURCE_DIR}/include/ElectroweakTheory)

aux_source_directory(. DIR_EWTHEORY_SRC)
add_library(ElectroweakTheory SHARED ${DIR_EWTHEORY_SRC})

install(TARGETS ElectroweakTheory
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/ElectroweakTheory/*.h)
#install(FILES ${loop_headers} DESTINATION include/ElectroweakTheory)

