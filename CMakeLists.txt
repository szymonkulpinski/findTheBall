cmake_minimum_required(VERSION 3.0.0)
project(findTheBall VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${YOUR_DIRECTORY}/include/main.hpp )



add_executable(findTheBall src/main.cpp)
target_link_libraries(findTheBall  ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
