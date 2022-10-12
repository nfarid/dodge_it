
###############################################################################
#                                                                             #
#                                                                             #
# This module defines the library SDL2::mixer                                 #
# This module define the variable SDL2_mixer_FOUND                            #
#                                                                             #
# Example:                                                                    #
#   find_package("SDL2_mixer" MODULE REQUIRED)                                #
#   target_link_libraries("my_app" PRIVATE "SDL2::mixer")                     #
#                                                                             #
###############################################################################


include("FindPackageHandleStandardArgs")
include("SelectLibraryConfigurations")



if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message(TRACE "Special handling for emscripten's SDL2_mixer")
    add_library("SDL2::mixer" IMPORTED INTERFACE)
    target_compile_options("SDL2::mixer" INTERFACE "-sUSE_SDL_MIXER=2")
    target_link_options("SDL2::mixer" INTERFACE "-sUSE_SDL_MIXER=2")
    set(SDL2_mixer_FOUND ON)
    return()
endif()



message(DEBUG "Looking for SDL's include directory")
find_path(SDL2_mixer_INCLUDE_DIRECTORY "SDL2/SDL_mixer.h"
    PATH_SUFFIXES "include"
)
message(VERBOSE "SDL2_mixer_INCLUDE_DIRECTORY: ${SDL2_mixer_INCLUDE_DIRECTORY}")



message(DEBUG "Looking for the SDL_mixer library")

message(DEBUG "Look for the release SDL_mixer library")
find_library(SDL2_mixer_LIBRARY_RELEASE
    NAMES "SDL2_mixer"
    PATH_SUFFIXES "lib"
)
message(VERBOSE "SDL2_mixer_LIBRARY_RELEASE: ${SDL2_mixer_LIBRARY_RELEASE}")

message(DEBUG "Look for the debug SDL_mixer library")
find_library(SDL2_mixer_LIBRARY_DEBUG
    NAMES "SDL2_mixerd" "SDL2_mixer"
    PATH_SUFFIXES "debug/lib" "lib"
)
message(VERBOSE "SDL2_mixer_LIBRARY_DEBUG: ${SDL2_mixer_LIBRARY_DEBUG}")

message(DEBUG "Set SDL2_mixer_LIBRARY to a suitable value using SelectLibraryConfigurations")
select_library_configurations("SDL2_mixer")
message(DEBUG "SDL2_mixer_LIBRARY: ${SDL2_mixer_LIBRARY}")



message(DEBUG "Using FindPackageHandleStandardArgs to handle arguments of find_package")
find_package_handle_standard_args("SDL2_mixer"
    REQUIRED_VARS SDL2_mixer_LIBRARY SDL2_mixer_INCLUDE_DIRECTORY
)
message(VERBOSE "SDL2_mixer_FOUND: ${SDL2_mixer_FOUND}")



message(DEBUG "Defining SDL2::mixer")
add_library("SDL2::mixer" IMPORTED UNKNOWN)
set_target_properties("SDL2::mixer" PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL2_mixer_INCLUDE_DIRECTORY}"
)

message(DEBUG "Add either the release or debug library to SDL2::mixer")
if(SDL2_mixer_LIBRARY_RELEASE)
    set_target_properties("SDL2::mixer" PROPERTIES
        IMPORTED_LOCATION_RELEASE "${SDL2_mixer_LIBRARY_RELEASE}"
    )
    set_property(TARGET "SDL2::mixer" APPEND PROPERTY
        IMPORTED_CONFIGURATIONS "RELEASE"
    )
endif()
if(SDL2_mixer_LIBRARY_DEBUG)
    set_target_properties("SDL2::mixer" PROPERTIES
        IMPORTED_LOCATION_DEBUG "${SDL2_mixer_LIBRARY_DEBUG}"
    )
    set_property(TARGET "SDL2::mixer" APPEND PROPERTY
        IMPORTED_CONFIGURATIONS "DEBUG"
    )
endif()
if( (NOT SDL2_mixer_LIBRARY_RELEASE) AND (NOT SDL2_mixer_LIBRARY_DEBUG) )
    set_target_properties("SDL2::mixer" PROPERTIES
        IMPORTED_LOCATION "${SDL2_mixer}"
    )
endif()


message(NOTICE "Library SDL2::mixer can now be linked to.")
