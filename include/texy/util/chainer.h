#pragma once

#include <funcy/util/static_checks.h>

#include <texy/mathop/chain.h>
#include <type_traits>

namespace texy
{
    /// @cond
    template < class Function >
    struct Chainer
    {
        decltype( auto ) operator()() const noexcept
        {
            return static_cast< const Function* >( this )->d0();
        }

        template < class Arg,
                   class = std::enable_if_t< !funcy::static_check::isFunction< Arg >() > >
        decltype( auto ) operator()( const Arg& x )
        {
            static_cast< Function* >( this )->update( x );
            return static_cast< const Function* >( this )->d0();
        }

        template < class OtherFunction,
                   class = std::enable_if_t< funcy::static_check::isFunction< OtherFunction >() > >
        auto operator()( const OtherFunction& g )
        {
            return mathop::Chain< Function, OtherFunction >(
                *static_cast< const Function* >( this ), g );
        }
    };
    /// @endcond
} // namespace texy
