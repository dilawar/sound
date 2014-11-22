//  moose/assert.hpp - SIMPLE_ASSERT(expr)
//                     SIMPLE_ASSERT_MSG(expr, msg)
//                     SIMPLE_VERIFY(expr)
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//  Copyright (c) Dilawar Singh 2013
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.moose.org/libs/utility/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// mooseinspect:naassert_macro
//
// Log: 
// Thursday 01 May 2014 01:18:02 PM IST
//
// This files is a modified version of boost/assert.hpp file. The names of
// macros have been changed.
//

//--------------------------------------------------------------------------------------//
//                                     SIMPLE_ASSERT                                     //
//--------------------------------------------------------------------------------------//

#undef SIMPLE_ASSERT

#if defined(SIMPLE_DISABLE_ASSERTS)

# define SIMPLE_ASSERT(expr) ((void)0)

#elif defined(SIMPLE_ENABLE_ASSERT_HANDLER)

#include "current_function.hpp"
#include <stringstream>

namespace moose
{
  void assertion_failed(char const * expr,
                        char const * function, char const * file, long line); // user defined
} // namespace moose

#define SIMPLE_ASSERT(expr) ((expr) \
  ? ((void)0) \
  : ::moose::assertion_failed(#expr, SIMPLE_CURRENT_FUNCTION, __FILE__, __LINE__))

#else
# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same
# define SIMPLE_ASSERT(expr) assert(expr)
#endif

//--------------------------------------------------------------------------------------//
//                                   SIMPLE_ASSERT_MSG                                   //
//--------------------------------------------------------------------------------------//

# undef SIMPLE_ASSERT_MSG

#if defined(SIMPLE_DISABLE_ASSERTS) || defined(NDEBUG)

  #define SIMPLE_ASSERT_MSG(expr, msg) ((void)0)

#elif defined(SIMPLE_ENABLE_ASSERT_HANDLER)

  #include "current_function.hpp"

  namespace moose
  {
    void assertion_failed_msg(char const * expr, char const * msg,
                              char const * function, char const * file, long line); // user defined
  } // namespace moose

  #define SIMPLE_ASSERT_MSG(expr, msg) ((expr) \
    ? ((void)0) \
    : ::moose::assertion_failed_msg(#expr, msg, SIMPLE_CURRENT_FUNCTION, __FILE__, __LINE__))

#else
  #ifndef SIMPLE_ASSERT_HPP
    #define SIMPLE_ASSERT_HPP
    #include <cstdlib>
    #include <iostream>
    #include "current_function.hpp"

    //  IDE's like Visual Studio perform better if output goes to std::cout or
    //  some other stream, so allow user to configure output stream:
    #ifndef SIMPLE_ASSERT_MSG_OSTREAM
    # define SIMPLE_ASSERT_MSG_OSTREAM std::cerr
    #endif

    namespace moose
    { 
      namespace assertion 
      { 
        namespace detail
        {
          inline void assertion_failed_msg(char const * expr, char const * msg, char const * function,
            char const * file, long line)
          {
            SIMPLE_ASSERT_MSG_OSTREAM
              << "***** Internal Program Error - assertion (" << expr << ") failed in "
              << function << ":\n"
              << file << '(' << line << "): " << msg << std::endl;
			#ifdef UNDER_CE
				// The Windows CE CRT library does not have abort() so use exit(-1) instead.
				std::exit(-1);
			#else
				std::abort();
			#endif
          }
        } // detail
      } // assertion
    } // detail
  #endif

  #define SIMPLE_ASSERT_MSG(expr, msg) ((expr) \
    ? ((void)0) \
    : ::moose::assertion::detail::assertion_failed_msg(#expr, msg, \
          SIMPLE_CURRENT_FUNCTION, __FILE__, __LINE__))
#endif

//--------------------------------------------------------------------------------------//
//                                     SIMPLE_VERIFY                                     //
//--------------------------------------------------------------------------------------//

#undef SIMPLE_VERIFY

#if defined(SIMPLE_DISABLE_ASSERTS) || ( !defined(MOOSE_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define SIMPLE_VERIFY(expr) ((void)(expr))

#else

# define SIMPLE_VERIFY(expr) MOOSE_ASSERT(expr)

/*-----------------------------------------------------------------------------
 *                                  SIMPLE_WARN
 *
 *  This macro accepts a stringstream like object as its second argument. First
 *  arguement is condition which must return a bool.
 *-----------------------------------------------------------------------------*/
#define SIMPLE_WARN(condition, msg) \
    if(! (condition) ) { \
        std::ostringstream ss; \
        ss << endl << "[WARN] " << msg; \
        std::cout << ss.str() \
        << std::endl; \
        std::cout << "\n\t|- " << "In function: " << SIMPLE_CURRENT_FUNCTION \
            << "\n\t+ In file: " << __FILE__ << ":" << __LINE__ << std::endl; \
    }

#endif
