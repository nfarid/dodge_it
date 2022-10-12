
###############################################################################
#                                                                             #
#                                                                             #
# This module defines the library SDL2::image                                 #
# This module define the variable SDL2_image_FOUND                            #
#                                                                             #
# Example:                                                                    #
#   find_package("SDL2_image" MODULE REQUIRED)                                #
#   target_link_libraries("my_app" PRIVATE "SDL2::image")                     #
#                                                                             #
###############################################################################


include("FindPackageHandleStandardArgs")
include("SelectLibraryConfigurations")



if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message(TRACE "Special handling for emscripten's SDL2_image")
    add_library("SDL2::image" IMPORTED INTERFACE)
    target_compile_options("SDL2::image" INTERFACE "-sUSE_SDL_IMAGE=2")
    target_link_options("SDL2::image" INTERFACE "-sUSE_SDL_IMAGE=2")
    set_target_properties("SDL2::image" PROPERTIES
        INTERFACE_COMPILE_OPTIONS "-sSDL2_IMAGE_FORMATS='[\"png\"]'"
        INTERFACE_LINK_OPTIONS "-sSDL2_IMAGE_FORMATS='[\"png\"]'"
    )
    set(SDL2_image_FOUND ON)
    return()
endif()



message(DEBUG "Looking for SDL's include directory")
find_path(SDL2_image_INCLUDE_DIRECTORY "SDL2/SDL_image.h"
    PATH_SUFFIXES "include"
)
message(VERBOSE "SDL2_image_INCLUDE_DIRECTORY: ${SDL2_image_INCLUDE_DIRECTORY}")



message(DEBUG "Looking for the SDL_image library")

message(DEBUG "Look for the release SDL_image library")
#vcpkg's debug sdl2-image library is called SDL_image and not SDL2_imaged
#This essentially means that this hackery is needed to make vcpkg find the release library
if(VCPKG_INSTALLED_DIR AND VCPKG_TARGET_TRIPLET)
    find_library(SDL2_image_LIBRARY_RELEASE
        NAMES "SDL2_image"
        HINTS "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib"
        NO_DEFAULT_PATH
    )
endif()
if(NOT SDL2_image_LIBRARY_RELEASE)
    find_library(SDL2_image_LIBRARY_RELEASE
        NAMES "SDL2_image"
        PATH_SUFFIXES "lib"
    )
endif()
message(VERBOSE "SDL2_image_LIBRARY_RELEASE: ${SDL2_image_LIBRARY_RELEASE}")

message(DEBUG "Look for the debug SDL_image library")
find_library(SDL2_image_LIBRARY_DEBUG
    NAMES "SDL2_imaged" "SDL2_image"
    PATH_SUFFIXES "debug/lib" "lib"
)
message(VERBOSE "SDL2_image_LIBRARY_DEBUG: ${SDL2_image_LIBRARY_DEBUG}")

message(DEBUG "Set SDL2_image_LIBRARY to a suitable value using SelectLibraryConfigurations")
select_library_configurations("SDL2_image")
message(DEBUG "SDL2_image_LIBRARY: ${SDL2_image_LIBRARY}")



message(DEBUG "Using FindPackageHandleStandardArgs to handle arguments of find_package")
find_package_handle_standard_args("SDL2_image"
    REQUIRED_VARS SDL2_image_LIBRARY SDL2_image_INCLUDE_DIRECTORY
)
message(VERBOSE "SDL2_image_FOUND: ${SDL2_image_FOUND}")



message(DEBUG "Defining SDL2::image")
add_library("SDL2::image" IMPORTED UNKNOWN)
set_target_properties("SDL2::image" PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL2_image_INCLUDE_DIRECTORY}"
)

message(DEBUG "Add either the release or debug library to SDL2::image")
if(SDL2_image_LIBRARY_RELEASE)
    set_target_properties("SDL2::image" PROPERTIES
        IMPORTED_LOCATION_RELEASE "${SDL2_image_LIBRARY_RELEASE}"
    )
    set_property(TARGET "SDL2::image" APPEND PROPERTY
        IMPORTED_CONFIGURATIONS "RELEASE"
    )
endif()
if(SDL2_image_LIBRARY_DEBUG)
    set_target_properties("SDL2::image" PROPERTIES
        IMPORTED_LOCATION_DEBUG "${SDL2_image_LIBRARY_DEBUG}"
    )
    set_property(TARGET "SDL2::image" APPEND PROPERTY
        IMPORTED_CONFIGURATIONS "DEBUG"
    )
endif()
if( (NOT SDL2_image_LIBRARY_RELEASE) AND (NOT SDL2_image_LIBRARY_DEBUG) )
    set_target_properties("SDL2::image" PROPERTIES
        IMPORTED_LOCATION "${SDL2_image}"
    )
endif()


message(NOTICE "Library SDL2::image can now be linked to.")
