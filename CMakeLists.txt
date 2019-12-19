cmake_minimum_required(VERSION 3.15)
project(programming_by_demonstration)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/datapoints.cpp src/demonstrations.cpp src/gmm.cpp src/gmr.cpp src/mvn.cpp src/EM_initilization.cpp src/kmeans_mlpack.cpp)
set(HEADER_FILES include/datapoints.h include/demonstrations.h include/gmm.h include/gmr.h include/mvn.h include/EM_initilization.h include/kmeans_mlpack.h)

add_executable(programming_by_demonstration ${SOURCE_FILES}  ${HEADER_FILES} )

#Matplotlib-cpp Libraries
find_package(PythonLibs 2.7)
#target_include_directories(programming_by_demonstration PRIVATE ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES})

## Armadillo Libraries and MLPACK Libraries
find_package(Armadillo 4.04 REQUIRED)

include_directories(include ${PYTHON_INCLUDE_DIRS} ${ARMADILLO_INCLUDE_DIRS} ${MLPACK_INCLUDE_DIRS})

find_library(ARMADILLO_LIBRARIES armadillo)
target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES}  ${ARMADILLO_LIBRARIES} libmlpack.so)

## MLPACK
#add extra include directories
#include_directories(/usr/local/include)
# add extra lib directories
#link_directories(/usr/lib/x86_64-linux-gnu)
#target_link_libraries(programming_by_demonstration libmlpack.so )




