# Untested with previous versions, yet should work
cmake_minimum_required(VERSION 3.6)

#set (CMAKE_CXX_FLAGS "-ftemplate-backtrace-limit=0")

project(bptsa VERSION 1.0.1 LANGUAGES CXX)

# Boost dependency
set(BOOST_ROOT CACHE PATH "Path to Boost library")
find_package(Boost 1.55 COMPONENTS serialization system)

# Create the target
#add_executable(${PROJECT_NAME} example_ptree_archive.cc ptree_oarchive.cc ptree_iarchive.cc basic_ptree_archive.cc)

add_library(bptsa SHARED ptree_oarchive.cc ptree_iarchive.cc basic_ptree_archive.cc)
set_target_properties(bptsa PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(bptsa PROPERTIES SOVERSION 1)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})


add_subdirectory(test)
