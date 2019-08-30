cmake_minimum_required(VERSION 3.1)

project(cell_model_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1 )

# OpenMP
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

# Pybind11
add_subdirectory(pybind11 ${CMAKE_BINARY_DIR}/pybind11)

set(source_dir "src")

set(source_files 
  ${source_dir}/Simulation.cpp
  ${source_dir}/Functions.cpp
  ${source_dir}/python_wrapper.cpp
)

set(header_files 
  ${source_dir}/Simulation.hpp
  ${source_dir}/Functions.hpp
)


pybind11_add_module(cell_model_cpp ${source_files} ${header_files})
target_link_libraries(cell_model_cpp PRIVATE ${libs})
target_include_directories(cell_model_cpp PRIVATE ${source_dir})
