list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if(USE_HOPPET)
    add_definitions(-DUSE_HOPPET)
    set(Hoppet_ROOT $ENV{Hoppet_ROOT_DIR})
    set(Hoppet_INCLUDE_DIRS $ENV{Hoppet_ROOT_DIR}/include)
    include_directories(${Hoppet_INCLUDE_DIRS})
endif(USE_HOPPET)

if(USE_HOPPET)
    add_library(hoppet INTERFACE)
    find_package(Hoppet REQUIRED)
    target_include_directories(hoppet SYSTEM INTERFACE ${Hoppet_INCLUDE_DIR})
    target_link_libraries(hoppet INTERFACE ${Hoppet_LIBRARY} gfortran)
endif(USE_HOPPET)

if(USE_APFEL)
    find_package(APFEL REQUIRED)
    find_package(apfelxx REQUIRED)
    add_definitions(-DUSE_APFEL)
    set(apfelxx_INCLUDE_DIRS $ENV{apfelxx_ROOT_DIR}/include)
    include_directories(${apfelxx_INCLUDE_DIRS})
endif(USE_APFEL)

include_directories(${CMAKE_SOURCE_DIR}/include/CTEQHelper)

aux_source_directory(. DIR_CTEQHELPER_SRC)
add_library(CTEQHelper SHARED ${DIR_CTEQHELPER_SRC})
if(USE_APFEL)
    target_link_libraries(CTEQHelper TOOL Figure Fantomas ${Hoppet_LIBRARY} Eigen3::Eigen APFEL::APFEL APFEL::APFELevol ${apfelxx_LIBRARIES})
else(USE_APFEL)
    target_link_libraries(CTEQHelper TOOL Figure Fantomas ${Hoppet_LIBRARY} Eigen3::Eigen)
endif(USE_APFEL)

install(TARGETS CTEQHelper
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

#file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/CTEQHelper/*.h)
#install(FILES ${loop_headers} DESTINATION include/CTEQHelper)
