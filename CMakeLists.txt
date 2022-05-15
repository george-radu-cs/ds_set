cmake_minimum_required(VERSION 3.5)

project(redblack VERSION 1.0)

add_library(queue
        QNode.h
        Queue.h
        Queue.cpp)

add_library(red_black
        RBNode.h
        RedBlackTree.h
        RedBlackTree.cpp)

# main exec
add_executable(redblack main.cpp)
# tests exec
add_executable(test1 test1.cpp)
add_executable(test2 test2.cpp)
add_executable(test3 test3.cpp)
add_executable(test4 test4.cpp)
add_executable(test5 test5.cpp)

target_link_libraries(redblack PRIVATE red_black)
target_link_libraries(redblack PRIVATE queue)

target_link_libraries(test1 PRIVATE red_black)
target_link_libraries(test1 PRIVATE queue)
target_link_libraries(test2 PRIVATE red_black)
target_link_libraries(test2 PRIVATE queue)
target_link_libraries(test3 PRIVATE red_black)
target_link_libraries(test3 PRIVATE queue)
target_link_libraries(test4 PRIVATE red_black)
target_link_libraries(test4 PRIVATE queue)
target_link_libraries(test5 PRIVATE red_black)
target_link_libraries(test5 PRIVATE queue)

target_compile_features(redblack PRIVATE cxx_lambda_init_captures)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
