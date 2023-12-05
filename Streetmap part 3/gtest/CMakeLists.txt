# 'Google_test' is the subproject name
project(Google_tests)


# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(p1_tests
        p1-node-tests.cpp
        p1-way-tests.cpp
        p1-sm-tests.cpp
        ../Node.h ../Node.cpp ../Way.h ../Way.cpp ../StreetMap.h ../StreetMap.cpp ../HashTable.h)
target_link_libraries(p1_tests gtest gtest_main)

add_executable(p2_hash
        p2-hash-tests.cpp p2-hash-extra.cpp ../HashTable.h)
target_link_libraries(p2_hash gtest gtest_main)


add_executable(p2_map
        p2-map-tests.cpp p2-map-extra.cpp
        ../Node.h ../Node.cpp ../Way.h ../Way.cpp ../StreetMap.h ../StreetMap.cpp ../HashTable.h)
target_link_libraries(p2_map gtest gtest_main)

add_executable(p3_graph
        p3-graph-tests.cpp ../Graph.h)
target_link_libraries(p3_graph gtest gtest_main)

add_executable(p3_map
        p3-map-tests.cpp
        ../Node.h ../Node.cpp ../Way.h ../Way.cpp ../StreetMap.h ../StreetMap.cpp
        ../Graph.h ../HashTable.h)
target_link_libraries(p3_map gtest gtest_main)