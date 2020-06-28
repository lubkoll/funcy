#pragma once

#define HAVE_BOOST

#ifdef HAVE_BOOST
#include <boost/math/constants/constants.hpp>
#endif

/// @cond
namespace funcy
{
#ifdef HAVE_BOOST
  constexpr double third() noexcept { return boost::math::constants::third<double>(); }
  constexpr double twothirds() noexcept { return boost::math::constants::twothirds<double>(); }
#else
  constexpr double third() noexcept { return 1./3.; }
  constexpr double twothirds() noexcept { return 2*third(); }
#endif
}
/// @endcond
