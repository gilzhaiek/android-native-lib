cmake_minimum_required(VERSION 3.4.1)

find_library(log-lib log )
add_library(extmath SHARED src/DumbCalc.cpp src/ExtMath.cpp)
target_link_libraries(extmath  ${log-lib})