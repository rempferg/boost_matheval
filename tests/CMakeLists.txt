# Build tests only when testing
set_directory_properties(PROPERTIES EXCLUDE_FROM_ALL ON)

# Add current directory to search path
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Find the Boost unit test framework
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBRARIES ${Boost_LIBRARIES})

# To add test cases easier we use the following function
function(UNIT_TEST)
  # Parse arguments
  cmake_parse_arguments(UT "" "TARGET" "SOURCE" ${ARGN} )
  # Add target for test and link with libraries
  add_executable(${UT_TARGET} ${UT_SOURCE})
  if(WITH_ASAN)
    set_source_files_properties(${UT_SOURCE}
      PROPERTIES COMPILE_FLAGS "-fsanitize=address,bounds,leak")
    set_target_properties(${UT_TARGET}
      PROPERTIES LINK_FLAGS "-fsanitize=address,bounds,leak")
  endif()
  if(MSVC)
    set_property(SOURCE ${UT_SOURCE} PROPERTY COMPILE_FLAGS "/DNOMINMAX")
  endif()
  target_link_libraries(${UT_TARGET} ${LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_compile_definitions(${UT_TARGET} PRIVATE "BOOST_TEST_DYN_LINK=1")
  # Tests are executed in the root directory
  add_test(NAME ${UT_TARGET} COMMAND ${UT_TARGET})
  add_dependencies(check ${UT_TARGET})
endfunction(UNIT_TEST)

# Add the tests
unit_test(TARGET literals SOURCE literals.cpp)
unit_test(TARGET arithmetic SOURCE arithmetic.cpp)
unit_test(TARGET order_of_operations SOURCE order_of_operations.cpp)
unit_test(TARGET unary SOURCE unary.cpp)
unit_test(TARGET functions SOURCE functions.cpp)
unit_test(TARGET variables SOURCE variables.cpp)