
#ifndef HPP_UTIL_GETDIR_741662071421_
#define HPP_UTIL_GETDIR_741662071421_

#include <filesystem>


namespace Util
{


namespace fs = std::filesystem;
using Path = fs::path;

/**
 * \brief Return the directory that contains the resources (doesn't end with seperator)
 * \throws runtime_error it cannot be obtained
 */
[[nodiscard]] Path getResDir();


}    // namespace Util

#endif // ifndef HPP_UTIL_GETDIR_741662071421_
