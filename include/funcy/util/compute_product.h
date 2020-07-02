#pragma once

#include "mathop_traits.h"
#include "type_traits.h"

#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < class X, class Y, bool bothPresent >
        struct ComputeProductImpl
        {
            static constexpr bool present = false;
            ComputeProductImpl( X const&, Y const& )
            {
            }
        };

        template < class X, class Y >
        struct ComputeProductImpl< X, Y, true >
        {
            static constexpr bool present = true;

            ComputeProductImpl( X const& x, Y const& y ) : value( multiply_via_traits( x(), y() ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            decay_t< decltype(
                multiply_via_traits( std::declval< X >()(), std::declval< Y >()() ) ) >
                value;
        };
    } // namespace detail
    template < class X, class Y >
    struct ComputeProduct : public detail::ComputeProductImpl< X, Y, X::present && Y::present >
    {
        ComputeProduct( X const& x, Y const& y )
            : detail::ComputeProductImpl < X,
        Y, X::present && Y::present > ( x, y )
        {
        }
    };

    template < class F, class G >
    auto product( const F& f, const G& g )
    {
        return ComputeProduct< F, G >( f, g );
    }
    /// @endcond
} // namespace funcy
