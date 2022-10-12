
#ifndef HPP_UTIL_MACROS_1658097308_
#define HPP_UTIL_MACROS_1658097308_

#include <cassert>

// Since static have multiple meanings
#define UTIL_INTERNAL static

// To explicitly state a constructor or conversion is implicit
// Since there's no [[implicit]] attribute
#define UTIL_IMPLICIT    /*[[implicit]]*/

// To explicitly state that a result type can be discarable
#define UTIL_DISCARDABLE /*[[discardable]]*/

// To explicitly state that a variable is intentionally not initialised
#define UTIL_UNINIT /*[[uninit]]*/


#ifdef __GNUC__
    #define UTIL_ALWAYS_INLINE inline __attribute__( (always_inline) )
#else
    #define UTIL_ALWAYS_INLINE inline
#endif  // ifdef __GNUC__

/*NO-FORMAT*/
#if defined( __GNUG__ )
    #define UTIL_UNREACHABLE() do{ assert(false && "unreachable"); __builtin_unreachable(); }while(false)
#elif defined( _MSC_VER )
    #define UTIL_UNREACHABLE() do{ assert(false && "unreachable"); __assume(0); }while(false)
#else
    #define UTIL_UNREACHABLE() do{ assert(false && "unreachable"); }while(false)
#endif    // if defined( __GNUG__ )
/*YES-FORMAT*/

#endif  // HPP_UTIL_MACROS_1658097308_
