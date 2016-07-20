project(jit_test)
cmake_minimum_required(VERSION 2.8)

macro(set_cpp_flag FLAG)
    if(${ARGC} GREATER 1)
        set(CMAKE_CXX_FLAGS_${ARGV1} "${CMAKE_CXX_FLAGS_${ARGV1}} ${FLAG}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
    endif()
endmacro()

set_cpp_flag("--std=c++11")
set_cpp_flag("-Wall")
set_cpp_flag("-Wl,--no-as-needed -ldl")

# Path to the SwiftShader git clone.
# SwiftShader libraries must be in PATH_TO_SWIFTSHADER_ROOT/build
# directory
set(PATH_TO_SWIFTSHADER_ROOT ../swiftshader)

include_directories(${PATH_TO_SWIFTSHADER_ROOT}/src)
include_directories(${PATH_TO_SWIFTSHADER_ROOT}/third_party/LLVM/include)
link_directories(${PATH_TO_SWIFTSHADER_ROOT}/build)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} pthread Reactor llvm SwiftShader)
