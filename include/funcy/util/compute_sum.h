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
        struct ComputeSumImpl
        {
            static constexpr bool present = false;
            ComputeSumImpl( const X&, const Y& )
            {
            }
        };

        template < class X, class Y >
        struct ComputeSumImpl< X, Y, true, true >
        {
            static constexpr bool present = true;

            ComputeSumImpl( const X& x, const Y& y ) : value( add_via_traits( x(), y() ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            remove_reference_t< decltype(
                add_via_traits( std::declval< X >()(), std::declval< Y >()() ) ) >
                value;
        };

        template < class X, class Y >
        struct ComputeSumImpl< X, Y, true, false >
        {
            static constexpr bool present = true;

            ComputeSumImpl( const X& x, const Y& ) : value( x() )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            decltype( std::declval< X >()() ) value;
        };

        template < class X, class Y >
        struct ComputeSumImpl< X, Y, false, true >
        {
            static constexpr bool present = true;

            ComputeSumImpl( const X&, const Y& y ) : value( y() )
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
    struct ComputeSum;

    template < class X, class Y >
    struct ComputeSum< X, Y > : public detail::ComputeSumImpl< X, Y >
    {
        ComputeSum( const X& x, const Y& y )
            : detail::ComputeSumImpl< X, Y, X::present, Y::present >( x, y )
        {
        }

        template < class F, class G, class... Args >
        ComputeSum( F const& f, G const& g, Args&&... args )
            : ComputeSum( X( f, args... ), Y( g, args... ) )
        {
        }
    };

    template < class X, class... Y >
    struct ComputeSum< X, Y... > : public ComputeSum< X, ComputeSum< Y... > >
    {
        ComputeSum( const X& x, const Y&... y )
            : ComputeSum< X, ComputeSum< Y... > >( x, ComputeSum< Y... >( y... ) )
        {
        }
    };

    template < class F, class... G >
    auto sum( F&& f, G&&... g )
    {
        return ComputeSum< std::decay_t< F >, std::decay_t< G >... >( std::forward< F >( f ),
                                                                      std::forward< G >( g )... );
    }
    /// @endcond
} // namespace funcy
