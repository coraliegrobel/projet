cmake_minimum_required(VERSION 2.6)

project(Projet_Motifs)

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)


add_executable(Motifs src/main.cpp src/case_two.cpp src/lecture.cpp src/case_one.cpp)

if (test)
enable_testing()
find_package(GTest)
if (NOT GTEST_FOUND)
link_directories(${CMAKE_SOURCE_DIR}/lib)
SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
SET(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
endif(NOT GTEST_FOUND)
add_executable(testMotifs src/testMotifs.cpp src/lecture.cpp src/case_two.cpp src/case_one.cpp)
target_link_libraries(testMotifs ${GTEST_BOTH_LIBRARIES} pthread)
add_test(Projet_Motifs testMotifs)
endif(test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)
