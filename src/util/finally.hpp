
#ifndef HPP_UTIL_FINALLY_1658097264_
#define HPP_UTIL_FINALLY_1658097264_

#include "macros.hpp"


namespace Util
{


/**
 *\brief A scope guard to make sure a function is called once and only once at the end of scope
 *
 *\example Finally f = []{cleanup();}; //cleanup is guaranteed to be called
 */
template<typename F>
class Finally final {
public:
    UTIL_IMPLICIT Finally( F&& lambda ) noexcept :
        m_func{static_cast<F&&>( lambda ) },
        m_valid{true}
    {}

    UTIL_IMPLICIT Finally(const F& lambda ) noexcept :
        m_func{lambda},
        m_valid{true}
    {}

    Finally& operator=(Finally&&) = delete;  // No move nor copy

    // m_func will be called once and only once by the end of Finally's scope
    ~Finally() noexcept {
        (*this)();
    }

    // func can be called early
    void operator()() noexcept {
        if(m_valid) {
            m_valid = false;
            m_func();
        }
    }

private:
    F m_func;
    bool m_valid{};
};


}// namespace Util

#endif  // HPP_UTIL_FINALLY_1658097264_
