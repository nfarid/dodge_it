
#include "resource_manager.hpp"

#include "../util/get_dir.hpp"

#include <SDL_FontCache/SDL_FontCache.h>

#include <SDL2/SDL_image.h>

#include <algorithm>
#include <stdexcept>
#include <typeinfo>

// filepath.string() behaviour is unspecified on windows
// reinterpret cast char8_t* to char* is legal but implementation defined
#define C_STR(FILEPATH) reinterpret_cast<const char*>( (FILEPATH).u8string().c_str() )


namespace Media
{


using namespace std::string_literals;
using std::string, std::runtime_error;


namespace
{


template<typename C, typename L> inline
auto find_if(const C& container, const L& lambda) {
    return std::find_if(container.begin(), container.end(), lambda);
}


template<typename Data> inline
auto findResource(const std::vector<Data>& resourceLst, std::string_view key) {
    const auto iter = find_if(resourceLst, [key](const Data& elem){return elem.key == key;});
    if(iter == cend(resourceLst) )
        throw runtime_error("Cannot find resource with key:" + string(key) + " of type:" + typeid(Data).name() );
    return iter->data.get();
}

template<typename Data> inline
void ensureResourceKeyDoesntExist(const std::vector<Data>& resourceLst, std::string_view key) {
    const auto iter = find_if(resourceLst, [key](const Data& elem){return elem.key == key;});
    if(iter != cend(resourceLst) ) {
        const string typeName = typeid(Data).name();
        const string keyName = string(key);
        throw runtime_error("Resource with key:" + keyName + " and type:" + typeName + "already exists");
    }
}


} // namespace


ResourceManager::ResourceManager(SDL_Renderer* renderer_) :
    rRenderer{renderer_}
{}

SDL_Texture* ResourceManager::getTexture(std::string_view key) const {
    return findResource(mTextureLst, key);
}

void ResourceManager::loadTexture(const std::filesystem::path& relativePath, std::string_view key) {
    ensureResourceKeyDoesntExist(mTextureLst, key);

    const auto absolutePath = Util::getResDir() / relativePath;

    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{
        IMG_Load(C_STR(absolutePath) ),
        &SDL_FreeSurface,
    };
    if(!surface)
        throw std::runtime_error("Can't load image: "s + C_STR(absolutePath) + "\n" + SDL_GetError() );

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{
        SDL_CreateTextureFromSurface(rRenderer, surface.get() ),
        &SDL_DestroyTexture,
    };
    if(!texture)
        throw std::runtime_error("Texture is invalid\n"s + SDL_GetError() );

    // mTextureLst.emplace_back(std::string(key), std::move(texture) ); //clang cannot compile this
    mTextureLst.push_back(TextureData{std::string(key), std::move(texture)});
}

void ResourceManager::clearTextures() {
    mTextureLst.clear();
}

Mix_Chunk* ResourceManager::getSoundEffect(std::string_view key) const {
    return findResource(mSoundEffectLst, key);
}

void ResourceManager::loadSoundEffect(const std::filesystem::path& relativePath, std::string_view key)
{
    ensureResourceKeyDoesntExist(mSoundEffectLst, key);

    const std::filesystem::path absolutePath = Util::getResDir() / relativePath;

    std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> sfx{
        Mix_LoadWAV(C_STR(absolutePath) ),
        &Mix_FreeChunk,
    };
    if(!sfx)
        throw std::runtime_error("Can't load sfx: "s + C_STR(absolutePath) + "\n" + Mix_GetError() );

    // mSoundEffectLst.emplace_back(string(key), std::move(sfx) ); //clang cannot compile this
    mSoundEffectLst.push_back(SoundEffectData{string(key), std::move(sfx)});
}

void ResourceManager::clearSoundEffects() {
    mSoundEffectLst.clear();
}

FC_Font* ResourceManager::getFont(std::string_view key) const {
    return findResource(mFontLst, key);
}

void ResourceManager::loadFont(const std::filesystem::path& relativePath, std::string_view key) {
    const auto absolutePath = Util::getResDir() / relativePath;
    std::unique_ptr<FC_Font, decltype(&FC_FreeFont)> font{FC_CreateFont(), &FC_FreeFont};
    // TODO: Add check for null (no point now since FC_CreateFont is broken if malloc returns null)

    // Font is size:20, colour:grey, style:normal
    // TODO: add options for these
    constexpr int fontSize = 20;
    constexpr SDL_Colour fontColour = {0x80, 0x80, 0x80, SDL_ALPHA_OPAQUE};
    constexpr auto fontStyle = TTF_STYLE_NORMAL;
    // Fc_LoadFont returns 0 on error, 1 on success
    if( !FC_LoadFont(font.get(), rRenderer, C_STR(absolutePath), fontSize, fontColour, fontStyle) )
        throw std::runtime_error("Can't load font: "s + C_STR(absolutePath) + "\n" + TTF_GetError() );

    // mFontLst.emplace_back(string(key), std::move(font) ); //clang cannot compile this
    mFontLst.push_back(FontData{string(key), std::move(font)});
}

void ResourceManager::clearFonts() {
    mFontLst.clear();
}


} // namespace Media

