#pragma once

#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

#include <utility>

namespace funcy
{
    /// @cond
    template < class X, class Y, bool both_present = X::present&& Y::present >
    struct ComputeProduct
    {
        static constexpr bool present = false;
        ComputeProduct( X const&, Y const& )
        {
        }
    };

    template < class X, class Y >
    struct ComputeProduct< X, Y, true >
    {
        static constexpr bool present = true;

        ComputeProduct( X const& x, Y const& y ) : value( multiply_via_traits( x(), y() ) )
        {
        }

        decltype( auto ) operator()() const
        {
            return value;
        }

        decay_t< decltype( multiply_via_traits( std::declval< X >()(), std::declval< Y >()() ) ) >
            value;
    };

    template < class F, class G >
    auto product( const F& f, const G& g )
    {
        return ComputeProduct< F, G >( f, g );
    }
    /// @endcond
} // namespace funcy
