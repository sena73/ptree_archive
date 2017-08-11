# Untested with previous versions, yet should work
cmake_minimum_required(VERSION 2.8.11)

project(example_bptsa)

# Boost dependency
set(BOOST_ROOT CACHE PATH "Path to Boost library")
find_package(Boost 1.55 COMPONENTS serialization system)

# Create the target
add_executable(${PROJECT_NAME} example_ptree_archive.cc ptree_oarchive.cc ptree_iarchive.cc basic_ptree_archive.cc)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES})
