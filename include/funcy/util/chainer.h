#pragma once

#include <funcy/concepts.h>
#include <funcy/mathop/chain.h>

namespace funcy
{
    /// @cond
    template < class F >
    struct Chainer
    {
        [[nodiscard]] decltype( auto ) operator()() const noexcept
        {
            return static_cast< const F* >( this )->d0();
        }

        template < class Arg >
        [[nodiscard]] decltype( auto ) operator()( const Arg& x ) requires( !Function< Arg > )
        {
            static_cast< F* >( this )->update( x );
            return static_cast< const F* >( this )->d0();
        }

        template < Function G >
        [[nodiscard]] constexpr auto operator()( G&& g )
        {
            return mathop::Chain( *static_cast< const F* >( this ), std::forward< G >( g ) );
        }
    };
    /// @endcond
} // namespace funcy
