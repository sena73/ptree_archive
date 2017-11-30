add_executable(test_aggregate_save extended_info2.cc extended_info.cc infobase.cc aggregate.cc test_aggregate_save.cc)
target_link_libraries(test_aggregate_save bpta)

add_executable(test_aggregate_load extended_info2.cc extended_info.cc infobase.cc aggregate.cc test_aggregate_load.cc)
target_link_libraries(test_aggregate_load bpta)

add_executable(test_derived_save extended_info2.cc extended_info.cc test_derived_save.cc infobase.cc derived_cast.cc)
target_link_libraries(test_derived_save bpta)

add_executable(test_derived_load extended_info2.cc extended_info.cc test_derived_load.cc infobase.cc derived_cast.cc)
target_link_libraries(test_derived_load bpta)

add_executable(test_version_save test_version_save.cc)
target_link_libraries(test_version_save bpta)

add_executable(test_version_load test_version_load.cc)
target_link_libraries(test_version_load bpta)
