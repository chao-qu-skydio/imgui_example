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

add_library(imgui "imgui/imgui.cpp" "imgui/imgui_draw.cpp"
                  "imgui/imgui_widgets.cpp" "imgui/imgui_tables.cpp")
target_include_directories(imgui PUBLIC "imgui")

add_library(imgui_gl "imgui/backends/imgui_impl_glfw.cpp"
                     "imgui/backends/imgui_impl_opengl3.cpp")
target_include_directories(imgui_gl PUBLIC "imgui/backends")
target_link_libraries(imgui_gl PUBLIC imgui glfw OpenGL::GL)

add_executable(imgui_demo "imgui/imgui_demo.cpp" "imgui_glfw_opengl3.cpp")
target_link_libraries(imgui_demo PUBLIC imgui_gl dl)
