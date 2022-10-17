# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(keyence_sdk VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/Samples/VC_Src/)
# source *.cpp
file(GLOB all_SRCS
		"${PROJECT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(keyence_lib_static STATIC ${all_SRCS})
# add .exe
add_executable(keyence_sdk ${all_SRCS})
# link againt static lib
target_link_libraries(keyence_sdk ${PROJECT_SOURCE_DIR}/Samples/VC_Src/Libx64/LKIF2.lib)
target_link_libraries(keyence_lib_static ${PROJECT_SOURCE_DIR}/Samples/VC_Src/Libx64/LKIF2.lib)
