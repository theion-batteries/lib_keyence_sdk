# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(whs_controller VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
## library name
set(WHS_CONTROLLER whs_controller)
set(WHS_CONTROLLER_STATIC ${whs_controller}-static)




# include libs
#include_directories(${PROJECT_SOURCE_DIR}/dep/sockpp/include/)
include_directories(${PROJECT_SOURCE_DIR}/Samples/VC_Src/)
# source *.cpp
file(GLOB all_SRCS
		"${PROJECT_SOURCE_DIR}/*.cpp"
		"${PROJECT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
#		"${PROJECT_SOURCE_DIR}/dep/sockpp/src/*.cpp"

)
# add .exe
add_executable(whs_controller ${all_SRCS})
# link againt static lib
target_link_libraries(whs_controller ${PROJECT_SOURCE_DIR}//Samples/VC_Src/Libx64/LKIF2.lib)
#target_link_libraries(whs_controller ${PROJECT_SOURCE_DIR}/dep/sockpp/build/Debug/sockpp-static.lib)