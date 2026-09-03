include_directories(${CMAKE_SOURCE_DIR}/include/Dictionary)
include_directories(${CMAKE_SOURCE_DIR}/include/Analysis)

execute_process(COMMAND rootcint -f DictionaryForCellInfo.C -c ${CMAKE_SOURCE_DIR}/include/Analysis/TreeForCellInfo.h 
                                                               ${CMAKE_SOURCE_DIR}/include/Analysis/LinkDef.h
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/Dictionary)

execute_process(COMMAND rootcint -f DictionaryForMadGraph.C -c ${CMAKE_SOURCE_DIR}/include/Analysis/TreeForMadGraph.h
                                                               ${CMAKE_SOURCE_DIR}/include/Analysis/ExRootClasses.h
                                                               ${CMAKE_SOURCE_DIR}/include/Analysis/ExRootAnalysisLinkDef.h
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/Dictionary)

#execute_process(COMMAND cp ${CMAKE_SOURCE_DIR}/src/Dictionary/DictionaryForCellInfo_rdict.pcm ${CMAKE_INSTALL_PREFIX}/lib)

message("Dictionary file has been generated.")
message("Do NOT forget move the .pcm file to running directory.")

aux_source_directory(. DIR_DIC_SRC)
add_library(Dictionary SHARED ${DIR_DIC_SRC})
target_link_libraries(Dictionary)

install(TARGETS Dictionary
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

