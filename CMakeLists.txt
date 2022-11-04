# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(keyence_sdk VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
###################### find library #############################
find_library( 
	KEYENCE_LIB 
	NAMES LKIF2.lib LKIF2.dll CmnLib.dll KeyUsbDrv.dll
	PATH "C:/vcpkg/installed/x64-windows/lib/libs"
	REQUIRED
)
find_path(
  KEYENCE_DIR
  NAMES LKIF2.h
  PATH "C:/vcpkg/installed/x64-windows/lib/libs/VC_Src" ${CMAKE_INSTALL_INCLUDEDIR}
)
list(APPEND CMAKE_MODULE_PATH "C:/vcpkg/installed/x64-windows/lib/libs")

###################### Build Library ############################

file(GLOB lib_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/keyence_client.cpp"
)
add_library(keyence_lib_static STATIC ${lib_SRCS})

target_link_libraries(keyence_lib_static ${KEYENCE_LIB})

target_include_directories(keyence_lib_static 
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/
)
set_target_properties(
    keyence_lib_static
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${KEYENCE_DIR}
      IMPORTED_LOCATION ${KEYENCE_LIB}
)

############################# build executable  ###################################


file(GLOB exe_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(keyence_exe ${exe_SRCS})

target_link_libraries(keyence_exe ${KEYENCE_LIB})

target_include_directories(keyence_exe 
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/
)

set_target_properties(
    keyence_exe
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${KEYENCE_DIR}
      IMPORTED_LOCATION ${KEYENCE_LIB}
)
