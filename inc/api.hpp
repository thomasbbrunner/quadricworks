
#pragma once

#ifdef OPENGL_ES // Including files for OpenGL ES

#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include <GLFW/glfw3.h>
/* main loop for OpenGL ES
#ifdef OPENGL_ES
    emscripten_set_main_loop(loop, 0, opengl.running());
#else
*/

#else // Including files for OpenGL

#include <glad/glad.h>
// GLFW has to be included after glad
// Including it only here solves compiling conflicts
#include <GLFW/glfw3.h>

#endif
