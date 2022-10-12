
add_executable("dodge_it"
    "main.cpp"
)



find_package("SDL2" MODULE REQUIRED)
find_package("SDL2_image" MODULE REQUIRED)
find_package("SDL2_mixer" MODULE REQUIRED)
find_package("SDL2_ttf" MODULE REQUIRED)
target_link_libraries("dodge_it"
    PRIVATE "SDL2::core"
    PRIVATE "SDL2::image"
    PRIVATE "SDL2::mixer"
    PRIVATE "SDL2::ttf"
    PRIVATE "SDL_FontCache"
)
