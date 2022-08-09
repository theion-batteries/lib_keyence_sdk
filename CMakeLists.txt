# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(keyence_sdk VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
## library name
set(keyence_sdk keyence_sdk)
set(keyence_sdk_STATIC ${keyence_sdk}-static)

# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/Samples/VC_Src/)
# source *.cpp
file(GLOB all_SRCS
		"${PROJECT_SOURCE_DIR}/*.cpp"
		"${PROJECT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${PROJECT_SOURCE_DIR}/src/*.cpp"

)
# add .exe
add_executable(keyence_sdk ${all_SRCS})
# link againt static lib
target_link_libraries(keyence_sdk ${PROJECT_SOURCE_DIR}//Samples/VC_Src/Libx64/LKIF2.lib)
