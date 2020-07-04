#pragma once

#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

#include <algorithm>
#include <utility>

namespace funcy
{
    template < class X, class Y, bool = X::present, bool = Y::present >
    struct ComputeConditional
    {
        static constexpr bool present = false;
        ComputeConditional( const X&, const Y&, bool )
        {
        }
    };

    template < class X, class Y >
    struct ComputeConditional< X, Y, true, true >
    {
        static constexpr bool present = true;

        ComputeConditional( const X& x, const Y& y, bool choose_x ) : value( choose_x ? x() : y() )
        {
        }

        decltype( auto ) operator()() const
        {
            return value;
        }

        remove_reference_t< decltype( std::declval< X >()() ) > value;
    };

    template < class X, class Y >
    struct ComputeConditional< X, Y, true, false >
    {
        static constexpr bool present = true;

        ComputeConditional( const X& x, const Y&, bool choose_x ) : value( choose_x ? x() : 0.0 )
        {
        }

        decltype( auto ) operator()() const
        {
            return value;
        }

        decltype( std::declval< X >()() ) value;
    };

    template < class X, class Y >
    struct ComputeConditional< X, Y, false, true >
    {
        static constexpr bool present = true;

        ComputeConditional( const X&, const Y& y, bool choose_x ) : value( choose_x ? 0.0 : y() )
        {
        }

        decltype( auto ) operator()() const
        {
            return value;
        }

        decltype( std::declval< Y >()() ) value;
    };
} // namespace funcy
