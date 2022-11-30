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
add_library(keyence_lib_static STATIC ${lib_SRCS})

target_link_libraries(keyence_lib_static ${KEYENCE_LIB} ${LKIF2dll} ${CmnLibdll} ${KeyUsbDrvdll} )

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
############################# install target lib ########################################
install(TARGETS keyence_lib_static DESTINATION lib)
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h"  "${KEYENCE_DIR}/*.h"
)
INSTALL(FILES ${files} DESTINATION include/keyence_lib_static/)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
  DESTINATION bin
  FILES_MATCHING PATTERN "*.dll")
# copy dlls one by one 
add_custom_command(TARGET keyence_lib_static POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:LKIF2dll> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:CmnLibdll> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:KeyUsbDrvdll> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>
COMMAND_EXPAND_LISTS

    )

############################# build executable  ###################################


file(GLOB exe_SRCS
		"${CMAKE_CURRENT_SOURCE_DIR}/Samples/VC_Src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_executable(keyence_exe ${exe_SRCS})

target_link_libraries(keyence_exe ${KEYENCE_LIB} ${LKIF2dll} ${CmnLibdll} ${KeyUsbDrvdll})

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

add_custom_command(TARGET keyence_exe POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:LKIF2dll> $<TARGET_FILE_DIR:keyence_exe>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:CmnLibdll> $<TARGET_FILE_DIR:keyence_exe>
COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:KeyUsbDrvdll> $<TARGET_FILE_DIR:keyence_exe>
COMMAND_EXPAND_LISTS

    )



     