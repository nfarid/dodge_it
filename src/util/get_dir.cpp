
#include "get_dir.hpp"

#include "macros.hpp"
#include "typedefs.hpp"

#ifdef _WIN32
    #include <Windows.h>
    #include <memory>
#endif // ifdef _WIN32


namespace Util
{


namespace
{


[[maybe_unused]] fs::path getExeDir() {
    static fs::path exeDir = []() -> fs::path{
#ifdef __linux__
        // Note that this is currently not that portable
        return fs::canonical(u8"/proc/self/exe").parent_path();
#elif defined(_WIN32)
        constexpr size_t maxBufferLength = 32768;
        std::unique_ptr<wchar_t[]> buffer;
        for(size_t bufferLength = 256; bufferLength <= maxBufferLength; bufferLength *= 2) {
            buffer.reset(new wchar_t[bufferLength]);
            const size_t pathLength = GetModuleFileNameW(nullptr, buffer.get(), bufferLength);
            // GetModuleFileNameW returns 0 on failure
            if(!pathLength)
                throw std::runtime_error("GetModuleFileNameW failed");
            // If it was truncated (not enough room) then pathLength >= bufferLength - 1
            if(pathLength < bufferLength - 1) {
                buffer[pathLength] = L'\0';
                break;
            }
        }
        return fs::path{buffer.get()}.parent_path();
#elif defined(__EMSCRIPTEN__)
        UTIL_UNREACHABLE();
#else
        static_assert(false, "Unsupported platform");
#endif // ifdef __linux__
    }();
    return exeDir;
}


} // namespace


Path getResDir() {
#ifdef __EMSCRIPTEN__
    return "data";
#else
    const static fs::path resource_directory = getExeDir().parent_path() / u8"share" / PROJECT_NAME;
    return resource_directory;
#endif // ifdef __EMSCRIPTEN__
}


} // namespace Util

