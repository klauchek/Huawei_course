cmake_minimum_required(VERSION 3.0.0)
project(quadratic_equation VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(quadratic_equation 

main.c
square_eq.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
