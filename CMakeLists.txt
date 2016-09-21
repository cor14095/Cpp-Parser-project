cmake_minimum_required(VERSION 3.6)
project(Cpp-Parser-project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Project1/main.cpp Project1/AST.cpp Project1/AST.h Project1/BinTree.cpp Project1/BinTree.h Project1/Graph.cpp Project1/Graph.h Project1/Node.cpp Project1/Node.h Project1/PostFix.cpp Project1/PostFix.h Project1/State.cpp Project1/State.h)
add_executable(executeme ${SOURCE_FILES})
