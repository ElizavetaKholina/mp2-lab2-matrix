set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(${target} ${srcs} ${hdrs})
#target_link_libraries(${vector} gtest ${MP2_LIBRARY})

add_executable(vector_test 
    test_tvector.cpp
    test_tmatrix.cpp
)

target_link_libraries(vector_test 
    gtest 
    test
)
target_include_directories(vector_test PRIVATE ${CMAKE_SOURCE_DIR})

