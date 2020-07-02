#pragma once

#include <funcy/util/chainer.h>

namespace funcy
{
    /// Wrap a constant.
    template < class Type >
    struct Constant : Chainer< Constant< Type > >
    {
        constexpr Constant() = default;

        /// Construct constant from copy.
        constexpr Constant( Type t_ ) : t( t_ )
        {
        }

        /// Function value.
        constexpr const Type& d0() const noexcept
        {
            return t;
        }

    private:
        Type t;
    };

    /**
     * @brief Generate a constant function that stores its argument as constant reference.
     *
     * This admits to use variable constant arguments, i.e. parameters that we want to study.
     */
    template < class Arg >
    auto const_ref( const Arg& x )
    {
        return Constant< const Arg& >( x );
    }

    /**
     * @brief Wrap a constant.
     * \return Constant<Arg>(x)
     */
    template < class Arg >
    constexpr auto constant( Arg x )
    {
        return Constant< Arg >( std::move( x ) );
    }
} // namespace funcy
