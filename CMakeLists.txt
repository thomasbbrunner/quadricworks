
# Project
cmake_minimum_required(VERSION 3.2)
project(quadric-engine)

# CMake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2") # -g -Og

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

# Executables
message(STATUS "Looking for main file in ${PROJECT_SOURCE_DIR}")
add_executable(quadric-engine
    ${PROJECT_SOURCE_DIR}/inc/api.cpp
    ${PROJECT_SOURCE_DIR}/src/study.cpp
    ${PROJECT_SOURCE_DIR}/inc/buffer.cpp
    ${PROJECT_SOURCE_DIR}/inc/camera.cpp
    ${PROJECT_SOURCE_DIR}/inc/math.cpp
    ${PROJECT_SOURCE_DIR}/inc/print.cpp
    ${PROJECT_SOURCE_DIR}/inc/scene.cpp
    ${PROJECT_SOURCE_DIR}/lib/glad/glad.c)

# Headers
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND) # forcing use of GLVND libs instead of legacy
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OPENGL_gl_LIBRARY}")
target_link_libraries(quadric-engine ${OPENGL_gl_LIBRARY})

# GLM
find_package(glm REQUIRED)
message(STATUS "Found glm in ${glm_DIR}")
target_link_libraries(quadric-engine glm::glm)

# GLFW
find_package(glfw3 REQUIRED)
message(STATUS "Found glfw3 in ${glfw3_DIR}")
target_link_libraries(quadric-engine glfw) 

# Glad
target_link_libraries(quadric-engine ${CMAKE_DL_LIBS}) # glad required libdl
set(GLAD_DIR ${PROJECT_SOURCE_DIR}/lib/glad)
add_custom_command(
    OUTPUT
        ${GLAD_DIR}/glad.c
    COMMAND
        glad --profile=core --generator=c-debug --spec=gl --out-path=${GLAD_DIR} --extensions= --local-files)
include_directories(${PROJECT_SOURCE_DIR}/lib/glad)

# Eigen
find_package(Eigen3 REQUIRED)
message(STATUS "Found Eigen in ${Eigen3_DIR}")
target_link_libraries(quadric-engine Eigen3::Eigen)
include_directories(${EIGEN3_INCLUDE_DIR}/unsupported)

# Old makefile recipe for cross-compiling with Emscripten for WebGL
# (for documentation)
# WCC = em++
# web:
# 	$ $(WCC) -Wall --std=c++11 -s USE_WEBGL2=1 -s FULL_ES3=1 -DOPENGL_ES -s USE_GLFW=3 --preload-file shaders -I $(INCLUDE_PATH) $(FILE_PATH) ./include/glad.c -lglfw -lrt -lm -ldl -o ./web/study$(FILE_NUM).html
