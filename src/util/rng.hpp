
#ifndef HPP_UTIL_RNG_
#define HPP_UTIL_RNG_

#include <random>


namespace Util
{


/**
 * @brief Very simple rng engine
 */
class Rng {
public:
    explicit Rng();

    float getFloat(float minimum, float maximum);

private:
    std::mt19937 mRngEngine;
};


}// namespace Util

#endif // ifndef HPP_UTIL_RNG_
