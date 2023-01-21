cmake_minimum_required(VERSION 3.24)
project(myproj LANGUAGES CXX CUDA)

enable_language(CUDA)

if(NOT DEFINED CMAKE_CUDA_STANDARD)
  set(CMAKE_CUDA_STANDARD 17)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(vector_add vector_add.cu)
target_include_directories(vector_add PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(vector_add PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# imgui
add_library(
  imgui
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_demo.cpp
  imgui/misc/cpp/imgui_stdlib.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui PUBLIC imgui imgui/backends)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL dl)
target_compile_definitions(imgui PUBLIC -DImDrawIdx=unsigned)

add_executable(imgui_demo imgui_glfw_opengl3.cpp)
target_link_libraries(imgui_demo PUBLIC imgui)

# implot
add_library(implot implot/implot.cpp implot/implot_items.cpp
                   implot/implot_demo.cpp)
target_include_directories(implot PUBLIC implot)
target_link_libraries(implot PUBLIC imgui)
target_compile_definitions(implot PUBLIC IMPLOT_DEBUG IMPLOT_DLL_EXPORT
                                         IMPLOT_BACKEND_ENABLE_OPENGL3)

add_executable(implot_demo implot_glfw_opengl3.cpp)
target_link_libraries(implot_demo PUBLIC implot)
