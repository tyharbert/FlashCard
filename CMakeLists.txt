cmake_minimum_required(VERSION 3.3)

# project declarations
project(fillin CXX)
project(multiple CXX)

#Evaluation program
add_executable(fillin fillin/fillin.cpp)
add_executable(multiple multiple/multiple.cpp)