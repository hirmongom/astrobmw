cmake_minimum_required(VERSION 3.31.10)

####################################################################################################
# Project definition
####################################################################################################
project(
  astrobmw_core
  LANGUAGES CXX
)

####################################################################################################
# C++ standard
####################################################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################################################################################
# Include directories
####################################################################################################
set(ASTRO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

####################################################################################################
# Library
####################################################################################################
file(GLOB_RECURSE ASTRO_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(astrobmw_core STATIC
  ${ASTRO_SOURCES}
)

target_include_directories(astrobmw_core
  PUBLIC ${ASTRO_INCLUDE_DIR}
)

# Place library in build/core/lib/
set_target_properties(astrobmw_core PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
)

####################################################################################################
# Tests
####################################################################################################
register_test_module(core)

set(TEST_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)

file(GLOB TEST_DIRS CONFIGURE_DEPENDS
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/*
)

foreach(test_dir ${TEST_DIRS})

  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_dir})

    set(test_target core_${test_dir})

    add_executable(${test_target} EXCLUDE_FROM_ALL
      tests/${test_dir}/main.cpp
    )

    target_link_libraries(${test_target}
      PRIVATE astrobmw_core
    )

    set_target_properties(${test_target} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}
    )

    register_test(core ${test_dir} ${test_target})

  endif()

endforeach()
