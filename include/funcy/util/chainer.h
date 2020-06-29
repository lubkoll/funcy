#pragma once

#include "static_checks.h"

#include <funcy/concepts.h>
#include <funcy/mathop/chain.h>

#include <type_traits>

namespace funcy
{
    /// @cond
    template < class F >
    struct Chainer
    {
        decltype( auto ) operator()() const noexcept
        {
            return static_cast< const F* >( this )->d0();
        }

        template < class Arg, class = std::enable_if_t< !Concepts::isFunction< Arg >() > >
        decltype( auto ) operator()( const Arg& x )
        {
            static_cast< F* >( this )->update( x );
            return static_cast< const F* >( this )->d0();
        }

        template < Function G >
        auto operator()( const G& g )
        {
            return mathop::Chain< F, G >( *static_cast< const F* >( this ), g );
        }
    };
    /// @endcond
} // namespace funcy
