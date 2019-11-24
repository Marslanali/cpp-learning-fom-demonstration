cmake_minimum_required(VERSION 3.15)
project(programming_by_demonstration)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/datapoints.cpp src/demonstrations.cpp src/gmm.cpp src/gmr.cpp src/mvn.cpp src/EM_initilization.cpp)
set(HEADER_FILES include/datapoints.h include/demonstrations.h include/gmm.h include/gmr.h include/mvn.h include/EM_initilization.h)

add_executable(programming_by_demonstration ${SOURCE_FILES}  ${HEADER_FILES})

find_package(Armadillo 5.4 REQUIRED)
include_directories(include ${ARMADILLO_INCLUDE_DIRS} )

find_library(ARMADILLO_LIBRARIES armadillo)
target_link_libraries(programming_by_demonstration ${ARMADILLO_LIBRARIES})

find_package(PythonLibs 2.7)
target_include_directories(programming_by_demonstration PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES})