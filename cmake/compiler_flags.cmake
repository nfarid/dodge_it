
include("CheckCXXCompilerFlag")

function(add_additional_warnings TARGET_NAME)
    set(WARNING_LIST
        #GCC and clang warnings
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Warray-bounds"
        "-Wcast-align"
        "-Wconversion"
        "-Wdangling-else"
        "-Wimplicit-fallthrough"
        "-Wfloat-equal"
        "-Winit-self"
        "-Wmain"
        "-Wmissing-declarations"
        "-Wnon-virtual-dtor"
        "-Wparentheses"
        "-Wpointer-arith"
        "-Wredundant-decls"
        "-Wswitch"
        "-Wstrict-overflow"
        "-Wuninitialized"
        "-Wundef"
        "-Wunreachable-code"
        "-Wunused"
        #Clang warnings
        "-Wcovered-switch-default"
        "-Wdeprecated"
        "-Wdeprecated-copy"
        "-Wdeprecated-copy-dtor"
        "-Wmissing-prototypes"
        "-Wmissing-variable-declarations"
        "-Wsuggest-destructor-override"
        "-Wnewline-eof"
        "-Wunused-exception-parameter"
    )

    #Only add the warning if it's accepted by the compiler
    foreach(WARNING ${WARNING_LIST})
        check_cxx_compiler_flag("${WARNING}" ACCEPT_${WARNING})
        if(ACCEPT_${WARNING})
            target_compile_options("${TARGET_NAME}" PRIVATE "${WARNING}")
        endif()
    endforeach()
endfunction()


function(treat_warnings_as_errors TARGET_NAME)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options("${TARGET_NAME}"
            PRIVATE "-Werror"
        )
    endif()
endfunction()
