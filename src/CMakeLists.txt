
add_executable("dodge_it"
    "main.cpp"

    "game/circle.hpp"
    "game/playing_state.cpp" "game/playing_state.hpp"

    "media/core.hpp"
    "media/camera.cpp" "media/camera.hpp"
    "media/drawable.cpp" "media/drawable.hpp"
    "media/game_context.hpp"
    "media/game_state.cpp" "media/game_state.hpp"
    "media/game_state_machine.cpp" "media/game_state_machine.hpp"
    "media/resource_manager.cpp" "media/resource_manager.hpp"
    "media/sprite.cpp" "media/sprite.hpp"
    "media/window.cpp" "media/window.hpp"

    "util/cstring_view.hpp"
    "util/dimension.hpp"
    "util/finally.hpp"
    "util/get_dir.cpp" "util/get_dir.hpp"
    "util/macros.hpp"
    "util/project_info.cpp" "util/project_info.hpp"
    "util/real.hpp"
    "util/rect.hpp"
    "util/typedefs.hpp"
    "util/vec2.hpp"
)


set_property(
    SOURCE "util/project_info.cpp"
    PROPERTY COMPILE_DEFINITIONS
    PROJECT_NAME="${PROJECT_NAME}"
    PROJECT_VERSION="${PROJECT_VERSION}"
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
