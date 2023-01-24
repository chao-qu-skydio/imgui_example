cmake_minimum_required(VERSION 3.21)
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
  imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp imgui/imgui_demo.cpp imgui/misc/cpp/imgui_stdlib.cpp)
target_include_directories(imgui PUBLIC imgui)
target_compile_definitions(imgui PUBLIC -DImDrawIdx=unsigned)

add_library(imgui_glfw imgui/backends/imgui_impl_glfw.cpp
                       imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui_glfw PUBLIC imgui/backends)
target_link_libraries(imgui_glfw PUBLIC imgui glfw OpenGL::GL dl)

add_executable(imgui_demo imgui_glfw.cpp)
target_link_libraries(imgui_demo PUBLIC imgui_glfw)

# implot
add_library(implot implot/implot.cpp implot/implot_items.cpp
                   implot/implot_demo.cpp)
target_include_directories(implot PUBLIC implot)
target_link_libraries(implot PUBLIC imgui_glfw)
target_compile_definitions(implot PUBLIC IMPLOT_DEBUG IMPLOT_DLL_EXPORT
                                         IMPLOT_BACKEND_ENABLE_OPENGL3)

add_executable(implot_demo implot_glfw.cpp)
target_link_libraries(implot_demo PUBLIC implot)

# imnodes
add_library(imnodes imnodes/imnodes.cpp)
target_include_directories(imnodes PUBLIC imnodes)
target_link_libraries(imnodes PUBLIC imgui_glfw)

add_executable(imnodes_demo node_editor.cpp imnodes_glfw.cpp)
target_link_libraries(imnodes_demo PUBLIC imnodes)
