cmake_minimum_required(VERSION 3.5.0)
project(proj2 VERSION 0.1.0)

# include(CTest)
# enable_testing()

add_executable(proj2 main.cpp vector.cpp city.cpp priority_queue.cpp pair.cpp hashmap.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
