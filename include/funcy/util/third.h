#pragma once

#ifdef FUNCY_BOOST_FOUND
#include <boost/math/constants/constants.hpp>
#endif

/// @cond
namespace funcy
{
#ifdef FUNCY_BOOST_FOUND
    constexpr double third() noexcept
    {
        return boost::math::constants::third< double >();
    }
    constexpr double twothirds() noexcept
    {
        return boost::math::constants::twothirds< double >();
    }
#else
    constexpr double third() noexcept
    {
        return 1. / 3.;
    }
    constexpr double twothirds() noexcept
    {
        return 2 * third();
    }
#endif
} // namespace funcy
/// @endcond
