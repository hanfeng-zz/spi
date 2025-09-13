cmake_minimum_required(VERSION 3.10)
project(SPI_DRIVERS C CXX)

# c lib
add_library(spix_c_lib  STATIC src/spi.c)
target_include_directories(spix_c_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/c
)

#c++ lib
add_library(spix_cplusplus_lib  STATIC src/spicplusplus.cpp)
target_include_directories(spix_cplusplus_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/cplusplus
)

#test
add_executable(spi_test test.cpp)
target_link_libraries(spi_test
    PRIVATE spix_c_lib
    PRIVATE spix_cplusplus_lib
)
