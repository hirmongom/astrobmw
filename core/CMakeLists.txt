cmake_minimum_required(VERSION 3.31.10)

project (
  astrobmw_core
  LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Base include directories for all targets
set(ASTRO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Collect and build all source files under src/
file(GLOB_RECURSE ASTRO_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(astrobmw_core STATIC
  ${ASTRO_SOURCES}
)

target_include_directories(astrobmw_core
  PUBLIC ${ASTRO_INCLUDE_DIR}
)

## Build all tests int tests/ automatically
file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/*)

foreach (test_dir ${TEST_DIRS})
  if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_dir})
    add_executable (${test_dir}
      tests/${test_dir}/main.cpp
    )

    target_include_directories(${test_dir}
      PRIVATE ${ASTRO_INCLUDE_DIR}
    )

    target_link_libraries(${test_dir}
      PRIVATE astrobmw_core
    )
  endif ()
endforeach ()

## Redirect all test binaries into build/tests/
set(TEST_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)

foreach (test_dir ${TEST_DIRS})
  if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_dir})
    set_target_properties(${test_dir} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}
    )
  endif ()
endforeach ()
