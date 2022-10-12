
#Pre-setup

cmake_minimum_required(VERSION "3.22.2")

include("cmake/util.cmake")

#compiler_commands.json is just overall useful
set(CMAKE_EXPORT_COMPILE_COMMANDS ON
    CACHE STRING "Create a compile_commands.json file"
)

if(DEFINED "ENV{VCPKG_ROOT}" AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    #Use vcpkg if VCPKG_ROOT is defined and there isn't a toolchain being used
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Try to use vcpkg.")
endif()
if("${VCPKG_TARGET_TRIPLET}" STREQUAL "x64-linux")
    #For some reason sdl doesn't build correct for the x64-linux triplet
    message(WARNING "Note that SDL doesn't work on vcpkg's x64-linux triplet")
endif()



#Setup

project("dodge_it"
    LANGUAGES "CXX"
    VERSION "0.1.0"
    DESCRIPTION "A simple game about dodging"
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR
        "In-source builds are not supported, please remove the `CMakeFiles'"
        "folder and `CMakeCache.txt', and create a folder for the build:"
        "mkdir build; cd build; cmake .."
    )
endif()

#This is for the cmake/FindLib.cmake files that is needed to find some libraries
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#I just liked the build folder being somewhat organised
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if("${IS_MULTI_CONFIG}")
    foreach(CONFIG_TYPE IN ITEMS ${CMAKE_CONFIGURATION_TYPES}) #it doesn't work if it's quoted
        string(TOUPPER "${CONFIG_TYPE}" UPPERCASE_CONFIG_TYPE)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPERCASE_CONFIG_TYPE} "${CMAKE_BINARY_DIR}/Binary_${CONFIG_TYPE}")
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPERCASE_CONFIG_TYPE} "${CMAKE_BINARY_DIR}/Library_${CONFIG_TYPE}")
        if(WIN32)
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPERCASE_CONFIG_TYPE} "${CMAKE_BINARY_DIR}/Binary_${CONFIG_TYPE}")
        else()
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPERCASE_CONFIG_TYPE} "${CMAKE_BINARY_DIR}/Library_${CONFIG_TYPE}")
        endif()
    endforeach()
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    if(WIN32) #windows require DLLs to be in the same folder as the executable (no rpaths)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    else()
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
    endif()
endif()

#Dealing with the asset directory
set(RES_SRC "${CMAKE_SOURCE_DIR}/data")
set(RES_DEST "${CMAKE_BINARY_DIR}/share/${PROJECT_NAME}")
symlink("${RES_SRC}" "${RES_DEST}")



#Actual builds

add_subdirectory("external/")
add_subdirectory("src/")
