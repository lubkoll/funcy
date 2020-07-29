#pragma once

#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < class X, class Y, bool = X::present, bool = Y::present >
        struct ComputeSubtractionImpl
        {
            static constexpr bool present = false;
            ComputeSubtractionImpl( const X&, const Y& )
            {
            }
        };

        template < class X, class Y >
        struct ComputeSubtractionImpl< X, Y, true, true >
        {
            static constexpr bool present = true;

            ComputeSubtractionImpl( const X& x, const Y& y )
                : value( subtract_via_traits( x(), y() ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            remove_reference_t< decltype(
                subtract_via_traits( std::declval< X >()(), std::declval< Y >()() ) ) >
                value;
        };

        template < class X, class Y >
        struct ComputeSubtractionImpl< X, Y, true, false >
        {
            static constexpr bool present = true;

            ComputeSubtractionImpl( const X& x, const Y& ) : value( x() )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            decltype( std::declval< X >()() ) value;
        };

        template < class X, class Y >
        struct ComputeSubtractionImpl< X, Y, false, true >
        {
            static constexpr bool present = true;

            ComputeSubtractionImpl( const X&, const Y& y ) : value( -y() )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            decltype( std::declval< Y >()() ) value;
        };
    } // namespace detail

    template < class... >
    struct ComputeSubtraction;

    template < class X, class Y >
    struct ComputeSubtraction< X, Y > : public detail::ComputeSubtractionImpl< X, Y >
    {
        ComputeSubtraction( const X& x, const Y& y )
            : detail::ComputeSubtractionImpl< X, Y, X::present, Y::present >( x, y )
        {
        }

        template < class F, class G, class... Args >
        ComputeSubtraction( F const& f, G const& g, Args&&... args )
            : ComputeSubtraction( X( f, args... ), Y( g, args... ) )
        {
        }
    };

    template < class X, class... Y >
    struct ComputeSubtraction< X, Y... >
        : public ComputeSubtraction< X, ComputeSubtraction< Y... > >
    {
        ComputeSubtraction( const X& x, const Y&... y )
            : ComputeSubtraction< X, ComputeSubtraction< Y... > >(
                  x, ComputeSubtraction< Y... >( y... ) )
        {
        }
    };
    /// @endcond
} // namespace funcy
