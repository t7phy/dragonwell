include_directories(${CMAKE_SOURCE_DIR}/include/Integration)

if(USE_JSON)
    add_definitions(-DUSE_JSON)
endif(USE_JSON)

aux_source_directory(. DIR_INTEGRATION_SRC)

if(NOT USE_JSON)
    list(REMOVE_ITEM DIR_INTEGRATION_SRC ./adaptive_gauss_batch.cpp
                                         ./adaptive_gauss_tree.cpp
                                         ./weights_loader.cpp
                                         ./laguerre_quadrature.cpp
                                         ./quadrature.cpp
                                         ./laguerre_singular_endpoint.cpp
                                         ./legendre_quadrature.cpp)
endif(NOT USE_JSON)

add_library(Integration SHARED ${DIR_INTEGRATION_SRC})

if(USE_JSON)
    target_link_libraries(Integration ${ROOT_LIBRARIES} nlohmann_json::nlohmann_json)
else(USE_JSON)
    target_link_libraries(Integration ${ROOT_LIBRARIES})
endif(USE_JSON)

install(TARGETS Integration
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

