
function(add_additional_warnings TARGET_NAME)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        #Add warnings for GCC and Clang
        target_compile_options("${TARGET_NAME}"
            PRIVATE "-Wall"
            PRIVATE "-Wextra"
            PRIVATE "-Wpedantic"
            PRIVATE "-Warray-bounds"
            PRIVATE "-Wcast-align"
            PRIVATE "-Wconversion"
            PRIVATE "-Wdangling-else"
            PRIVATE "-Wimplicit-fallthrough"
            PRIVATE "-Wfloat-equal"
            PRIVATE "-Winit-self"
            PRIVATE "-Wmain"
            PRIVATE "-Wmissing-declarations"
            PRIVATE "-Wnon-virtual-dtor"
            PRIVATE "-Wparentheses"
            PRIVATE "-Wpointer-arith"
            PRIVATE "-Wredundant-decls"
            PRIVATE "-Wswitch"
            PRIVATE "-Wstrict-overflow"
            PRIVATE "-Wuninitialized"
            PRIVATE "-Wundef"
            PRIVATE "-Wunreachable-code"
            PRIVATE "-Wunused"
        )
        #Clang has additional warnings
        if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options("${TARGET_NAME}"
                PRIVATE "-Wcovered-switch-default"
                PRIVATE "-Wdeprecated"
                PRIVATE "-Wdeprecated-copy"
                PRIVATE "-Wdeprecated-copy-dtor"
                PRIVATE "-Wmissing-prototypes"
                PRIVATE "-Wmissing-variable-declarations"
                PRIVATE "-Wsuggest-destructor-override"
                PRIVATE "-Wnewline-eof"
                PRIVATE "-Wunused-exception-parameter"
            )
        endif()
    endif()
endfunction()


function(treat_warnings_as_errors TARGET_NAME)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options("${TARGET_NAME}"
            PRIVATE "-Werror"
        )
    endif()
endfunction()
