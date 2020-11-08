# Project definition
cmake_minimum_required(VERSION 3.1)
project(marchingCubes)

## GLFW
add_subdirectory("./libs/glfw-3.3.2/glfw-3.3.2") ###!
include_directories("${GLFW_SOURCE_DIR}/deps")
include_directories(${glfw_INCLUDE_DIRS})

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/src/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
           "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
                "${GLFW_SOURCE_DIR}/deps/tinycthread.c")

## GLM
include_directories("./libs/glm-0.9.9.7/glm")


## MAIN PROGRAM SRC
include_directories("./headers")
FILE(GLOB SRCFOLDERFILES "./src/*.cpp")

## COMPILING AND LINKING
add_executable(main ${SRCFOLDERFILES} ${TINYCTHREAD} ${GETOPT} ${GLAD})

target_link_libraries(main glfw ${GLFW_LIBRARIES})