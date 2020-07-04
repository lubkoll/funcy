#pragma once

#include <funcy/util/type_traits.h>

#include <utility>

namespace funcy
{
    /// @cond
    namespace detail
    {
        template < class X, class Y, bool bothPresent >
        struct ComputeDotImpl
        {
            static constexpr bool present = false;
            ComputeDotImpl( X const&, Y const& )
            {
            }
        };

        template < class X, class Y >
        struct ComputeDotImpl< X, Y, true >
        {
            static constexpr bool present = true;

            ComputeDotImpl( X const& x, Y const& y ) : value( x().dot( y() ) )
            {
            }

            decltype( auto ) operator()() const
            {
                return value;
            }

            decay_t< decltype( std::declval< X >()().dot( std::declval< Y >()() ) ) > value;
        };
    } // namespace detail

    template < class X, class Y >
    struct ComputeDot : public detail::ComputeDotImpl< X, Y, X::present && Y::present >
    {
        ComputeDot( X const& x, Y const& y )
            : detail::ComputeDotImpl < X,
        Y, X::present && Y::present > ( x, y )
        {
        }
    };

    template < class F, class G >
    auto dot_impl( const F& f, const G& g )
    {
        return ComputeDot< F, G >( f, g );
    }
    /// @endcond
} // namespace funcy
