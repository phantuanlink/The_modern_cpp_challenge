cmake_minimum_required (VERSION 3.7.0) 
project(problem_01)

add_executable(problem_01 main.cpp)
target_link_libraries(problem_01 PRIVATE spdlog::spdlog_header_only)

set_target_properties (problem_01 PROPERTIES FOLDER "01.Math")