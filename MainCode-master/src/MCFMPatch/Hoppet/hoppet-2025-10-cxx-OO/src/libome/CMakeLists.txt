#set(LIBOME_DIR ${PROJECT_SOURCE_DIR}/external-code/libome/src)
#set(CXXINCLUDE ${CXXINCLUDE} ${LIBOME_DIR} PARENT_SCOPE)
#
#file(GLOB LIBOME_SOURCES_CXX ${LIBOME_DIR}/ome/A*.cpp)
#set(LIBOME_SOURCES_CXX ${LIBOME_SOURCES_CXX} ${PROJECT_SOURCE_DIR}/src/libome/hoppet_libome_cxx.cc)
#
## make sure we modify the parent-scope variable
#set(SOURCESCXX ${SOURCESCXX} ${LIBOME_SOURCES_CXX} PARENT_SCOPE)
#set(SOURCESf90 ${SOURCESf90} src/libome/hoppet_libome_fortran.f90 PARENT_SCOPE)

option(HOPPET_USE_EXTERNAL_LIBOME "Use external libome instead of bundled source" ON)

if(HOPPET_USE_EXTERNAL_LIBOME)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(libome REQUIRED IMPORTED_TARGET libome)

    set(CXXINCLUDE ${CXXINCLUDE} ${libome_INCLUDE_DIRS} PARENT_SCOPE)

    set(SOURCESCXX
        ${SOURCESCXX}
        ${PROJECT_SOURCE_DIR}/src/libome/hoppet_libome_cxx.cc
        PARENT_SCOPE
    )

    set(SOURCESf90
        ${SOURCESf90}
        src/libome/hoppet_libome_fortran.f90
        PARENT_SCOPE
    )

    #target_link_libraries(hoppet PRIVATE PkgConfig::libome)

else()
    set(LIBOME_DIR ${PROJECT_SOURCE_DIR}/external-code/libome/src)
    set(CXXINCLUDE ${CXXINCLUDE} ${LIBOME_DIR} PARENT_SCOPE)

    file(GLOB LIBOME_SOURCES_CXX ${LIBOME_DIR}/ome/A*.cpp)
    set(LIBOME_SOURCES_CXX
        ${LIBOME_SOURCES_CXX}
        ${PROJECT_SOURCE_DIR}/src/libome/hoppet_libome_cxx.cc
    )

    set(SOURCESCXX ${SOURCESCXX} ${LIBOME_SOURCES_CXX} PARENT_SCOPE)
    set(SOURCESf90 ${SOURCESf90} src/libome/hoppet_libome_fortran.f90 PARENT_SCOPE)
endif()
