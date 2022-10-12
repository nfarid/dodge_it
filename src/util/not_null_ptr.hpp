
#ifndef HPP_UTIL_NOTNULLPTR_9311664104144_
#define HPP_UTIL_NOTNULLPTR_9311664104144_

#include <cstddef>
#include <stdexcept>

#include "macros.hpp"


namespace Util
{


using std::nullptr_t;

template<typename T>
class NotNullPtr {
public:
    UTIL_IMPLICIT NotNullPtr() = delete;
    UTIL_IMPLICIT NotNullPtr(nullptr_t) = delete;
    NotNullPtr& operator=(nullptr_t) = delete;

    constexpr UTIL_IMPLICIT UTIL_ALWAYS_INLINE NotNullPtr(T* p_) :
        mPtr{p_}
    {
        if(!p_)
            throw std::invalid_argument("NotNullPtr cannot be null");
    }

    constexpr UTIL_ALWAYS_INLINE NotNullPtr& operator=(T* p_) {
        if(!p_)
            throw std::invalid_argument("NotNullPtr cannot be null");
        mPtr = p_;
        return *this;
    }

    constexpr UTIL_IMPLICIT UTIL_ALWAYS_INLINE operator T*() {
        return mPtr;
    }

private:
    T* mPtr;
};


}// namespace Util

#endif // ifndef HPP_UTIL_NOTNULLPTR_9311664104144_
