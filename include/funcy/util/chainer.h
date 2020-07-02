#pragma once

#include <funcy/concepts.h>
#include <funcy/mathop/chain.h>

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

        template < class Arg >
        decltype( auto ) operator()( const Arg& x ) requires( !Function< Arg > )
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
