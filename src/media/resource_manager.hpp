
#ifndef HPP_MEDIA_RESOURCEMANAGER_3311664024594_
#define HPP_MEDIA_RESOURCEMANAGER_3311664024594_

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

struct FC_Font;


namespace Media
{


namespace fs = std::filesystem;


class ResourceManager {
public:
    explicit ResourceManager(SDL_Renderer* renderer_);

    [[nodiscard]] SDL_Texture* getTexture(std::string_view key) const;
    void loadTexture(const fs::path& relativePath, std::string_view key);
    void clearTextures();

    [[nodiscard]] Mix_Chunk* getSoundEffect(std::string_view key) const;
    void loadSoundEffect(const std::filesystem::path& relativePath, std::string_view key);
    void clearSoundEffects();

    [[nodiscard]] FC_Font* getFont(std::string_view key) const;
    void loadFont(const std::filesystem::path& relativePath, std::string_view key);
    void clearFonts();

private:
    struct TextureData {
        std::string key;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> data;
    };
    struct SoundEffectData {
        std::string key;
        std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> data;
    };
    struct FontData {
        std::string key;
        std::unique_ptr<FC_Font, void(*)(FC_Font*)> data;
    };


    std::vector<TextureData> mTextureLst{};
    std::vector<SoundEffectData> mSoundEffectLst{};
    std::vector<FontData> mFontLst{};
    SDL_Renderer* rRenderer{};
};


}// namespace Media

#endif // ifndef HPP_MEDIA_RESOURCEMANAGER_3311664024594_
