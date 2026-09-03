# Try to find apfelxx
# Defines:
#   apfelxx_FOUND
#   apfelxx_INCLUDE_DIR
#   apfelxx_INCLUDE_DIRS (not cached)
#   apfelxx_LIBRARY
#   apfelxx_LIBRARIES (not cached)
#   apfelxx_LIBRARY_DIR (not cached)

find_library(apfelxx_LIBRARY NAMES apfelxx
    HINTS $ENV{apfelxx_ROOT_DIR}/lib ${apfelxx_ROOT_DIR}/lib)

IF(${apfelxx_LIBRARY} MATCHES "apfelxx_LIBRARY-NOTFOUND")
    FIND_PROGRAM(apfelxx_CONFIG_EXECUTABLE NAMES apfelxx-config
        HINTS $ENV{apfelxx_ROOT_DIR}/bin ${apfelxx_ROOT_DIR}/bin)
    IF(${apfelxx_CONFIG_EXECUTABLE} MATCHES "apfelxx_CONFIG_EXECUTABLE-NOTFOUND")
        MESSAGE(STATUS "Looking for apfelxx... apfelxx-config executable not found")
    ELSE(${apfelxx_CONFIG_EXECUTABLE} MATCHES "apfelxx_CONFIG_EXECUTABLE-NOTFOUND")
        MESSAGE(STATUS "Looking for apfelxx... using apfelxx-config executable")
        EXEC_PROGRAM(${apfelxx_CONFIG_EXECUTABLE} ARGS "--prefix" OUTPUT_VARIABLE apfelxx_PREFIX)
        find_library(apfelxx_LIBRARY NAMES apfelxx PATHS ${apfelxx_PREFIX}/lib)
    ENDIF(${apfelxx_CONFIG_EXECUTABLE} MATCHES "apfelxx_CONFIG_EXECUTABLE-NOTFOUND")
ENDIF(${apfelxx_LIBRARY} MATCHES "apfelxx_LIBRARY-NOTFOUND")

find_path(apfelxx_INCLUDE_DIR apfel/apfelxx.h
    HINTS $ENV{apfelxx_ROOT_DIR}/include ${apfelxx_ROOT_DIR}/include ${apfelxx_PREFIX}/include)

mark_as_advanced(apfelxx_LIBRARY apfelxx_INCLUDE_DIR)

# handle QUIETLY and REQUIRED arguments and set apfel_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(apfelxx DEFAULT_MSG apfelxx_INCLUDE_DIR apfelxx_LIBRARY)

set(apfelxx_LIBRARIES ${apfelxx_LIBRARY})
get_filename_component(apfelxx_LIBRARY_DIRS ${apfelxx_LIBRARY} PATH)

set(apfelxx_INCLUDE_DIRS ${apfelxx_INCLUDE_DIR})

mark_as_advanced(apfelxx_FOUND)

