cmake_minimum_required(VERSION 3.31.10)

####################################################################################################
# Project Definition
####################################################################################################
project(
  astrobmw
  LANGUAGES CXX
)

####################################################################################################
# Safety checks
####################################################################################################
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed. Use: cmake -S . -B build")
endif()

####################################################################################################
# Enable CTest
####################################################################################################
include(CTest)
enable_testing()

####################################################################################################
# Test orchestration framework
####################################################################################################
# Register module function
function(register_test_module module)

  add_custom_target(${module}_tests)

  add_custom_target(run_${module}_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
      --output-on-failure
      -R "^${module}_"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )

  add_dependencies(all_tests ${module}_tests)
  add_dependencies(run_all_tests ${module}_tests)
endfunction()

# Register individual test
function(register_test module test_name exe_target)

  set(full_name "${module}_${test_name}")

  add_test(NAME ${full_name} COMMAND ${exe_target})

  add_dependencies(${module}_tests ${exe_target})

  add_custom_target(run_test_${full_name}
    COMMAND ${CMAKE_CTEST_COMMAND}
      --output-on-failure
      -R "^${full_name}$"
    DEPENDS ${exe_target}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )

  add_dependencies(run_${module}_tests ${full_name})

endfunction()

# Global targets
add_custom_target(all_tests)

add_custom_target(run_all_tests
  COMMAND ${CMAKE_CTEST_COMMAND}
    --output-on-failure
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

####################################################################################################
# Subdirectories
####################################################################################################
add_subdirectory(core)
add_subdirectory(cli)
