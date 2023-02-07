# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.1.0)

# project name
project(keyence_sdk VERSION "1.0")

# set the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
###################### find library #############################
find_library( KEYENCE_LIB 
	NAMES "LKIF2.lib"
	PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/Libx64/"
	NO_DEFAULT_PATH
  REQUIRED
)

find_path(
  KEYENCE_DIR
  NAMES LKIF2.h
  NO_DEFAULT_PATH
  HINTS "${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/"
)

message("found keyence static lib ${KEYENCE_LIB}")
message("found keyence includes ${KEYENCE_DIR}")

add_library( LKIF2dll SHARED IMPORTED  GLOBAL)
set_target_properties( LKIF2dll PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/Libx64/LKIF2.dll)

add_library( CmnLibdll SHARED IMPORTED  GLOBAL)
set_target_properties( CmnLibdll PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/Libx64/CmnLib.dll)

add_library( KeyUsbDrvdll SHARED IMPORTED  GLOBAL)
set_target_properties( KeyUsbDrvdll PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/Libx64/KeyUsbDrv.dll)
###################### Build Library ############################

file(GLOB lib_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/keyence_client.cpp"
)
add_library(keyenceLib STATIC ${lib_SRCS})

target_link_libraries(keyenceLib ${KEYENCE_LIB} ${LKIF2dll} ${CmnLibdll} ${KeyUsbDrvdll} )

target_include_directories(keyenceLib 
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/
)
set_target_properties(
    keyenceLib
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${KEYENCE_DIR}
      IMPORTED_LOCATION ${KEYENCE_LIB}
)
# copy dlls one by one 
function(copy_dlls_keyence_target_destination target_exe)
add_custom_command(TARGET ${target_exe} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:LKIF2dll> $<TARGET_FILE_DIR:${target_exe}>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:CmnLibdll> $<TARGET_FILE_DIR:${target_exe}>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:KeyUsbDrvdll> $<TARGET_FILE_DIR:${target_exe}>
COMMAND_EXPAND_LISTS)
endfunction()

############################# build executable  ###################################

file(GLOB exe_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(keyenceBin ${exe_SRCS})

target_link_libraries(keyenceBin ${KEYENCE_LIB} ${LKIF2dll} ${CmnLibdll} ${KeyUsbDrvdll})

target_include_directories(keyenceBin 
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/includes/
PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/
)

set_target_properties(
    keyenceBin
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${KEYENCE_DIR}
      IMPORTED_LOCATION ${KEYENCE_LIB}
)

copy_dlls_keyence_target_destination(keyenceBin)


############################# install target lib ########################################
install(TARGETS keyenceLib DESTINATION lib
)

copy_dlls_keyence_target_destination(keyenceLib)

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h"  "${KEYENCE_DIR}/*.h"
)
install(FILES ${files} DESTINATION include/keyenceLib/)
FILE(GLOB keyence_dlls  "${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/Libx64/*.dll"  )
install(FILES ${keyence_dlls} DESTINATION ${CMAKE_INSTALL_BINDIR})


