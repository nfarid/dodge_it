
#include "rng.hpp"

#include <cassert>
#include <chrono>


namespace Util
{


namespace
{


// TODO: check out random_device and other random methods
// for now just use current time
auto getSeed() {
    const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    return static_cast<std::mt19937::result_type>(seed);
}


} // namespace


Rng::Rng() :
    mRngEngine{getSeed()}
{}

float Rng::getFloat(float minimum, float maximum) {
    assert(minimum <= maximum);
    assert(maximum - minimum <= std::numeric_limits<float>::max() );
    std::uniform_real_distribution distr{minimum, maximum};
    return distr(mRngEngine);
}


} // namespace Util

