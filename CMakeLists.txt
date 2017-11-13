# Untested with previous versions, yet should work
cmake_minimum_required(VERSION 3.6)

#set (CMAKE_CXX_FLAGS "-ftemplate-backtrace-limit=0")

project(bpta VERSION 1.0.1 LANGUAGES CXX)

# Boost dependency
set(BOOST_ROOT CACHE PATH "Path to Boost library")
find_package(Boost 1.55 COMPONENTS serialization system)


add_library(bpta SHARED ptree_oarchive.cc ptree_iarchive.cc basic_ptree_archive.cc)
set_target_properties(
  bpta
  PROPERTIES
    FRAMEWORK ON
    SOVERSION 1
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER "basic_ptree_archive.hh;ptree_iarchive.hh;ptree_oarchive.hh"
    ARCHIVE_OUTPUT_DIRECTORY "lib"
    LIBRARY_OUTPUT_DIRECTORY "lib"
)


include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

INSTALL(TARGETS bpta
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/boost/archive
)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})


add_subdirectory(test)
