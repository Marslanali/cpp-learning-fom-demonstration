cmake_minimum_required(VERSION 3.15)
project(programming_by_demonstration)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/datapoints.cpp src/demonstrations.cpp src/gmm.cpp src/gmr.cpp src/mvn.cpp src/EM_initilization.cpp src/kmeans_mlpack.cpp)
set(HEADER_FILES include/datapoints.h include/demonstrations.h include/gmm.h include/gmr.h include/mvn.h include/EM_initilization.h include/kmeans_mlpack.h)

add_executable(programming_by_demonstration ${SOURCE_FILES}  ${HEADER_FILES} )

## Armadillo Libraries and MLPACK Libraries
find_package(Armadillo 5.04 REQUIRED)
#Matplotlib-cpp Libraries
find_package(PythonLibs 2.7)

# find libraries
find_library(ARMADILLO_LIBRARIES armadillo)

#target includes
include_directories(include ${PYTHON_INCLUDE_DIRS} ${ARMADILLO_INCLUDE_DIRS} ${MLPACK_INCLUDE_DIRS})

#target link .so libraries
target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES}  ${ARMADILLO_LIBRARIES} libmlpack.so)


#target_include_directories(programming_by_demonstration PRIVATE ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES})

## MLPACK
#add extra include directories
#include_directories(/usr/local/include)
# add extra lib directories
#link_directories(/usr/lib/x86_64-linux-gnu)
#target_link_libraries(programming_by_demonstration libmlpack.so )




