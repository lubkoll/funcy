#pragma once

#include <funcy/util/chainer.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    /// %Identity mapping \f$ f(x)=x \f$.
    template < class Arg >
    struct Identity : Chainer< Identity< Arg > >
    {
        /// Default constructor.
        Identity() = default;

        /**
         * @brief Constructor.
         * @param x point of evaluation.
         */
        Identity( const Arg& x ) noexcept( std::is_copy_constructible_v< Arg > ) : x_( x )
        {
        }

        /**
         * @brief Constructor.
         * @param x point of evaluation.
         */
        Identity( Arg&& x ) noexcept( std::is_move_constructible_v< Arg > ) : x_( std::move( x ) )
        {
        }

        /// Reset point of evaluation
        void update( const Arg& x )
        {
            x_ = x;
        }

        /// Function value.
        const Arg& d0() const noexcept
        {
            return x_;
        }

        /// First directional derivative.
        template < int >
        const Arg& d1( const Arg& dx ) const noexcept
        {
            return dx;
        }

    private:
        Arg x_;
    };

    /// Construct Identity<Arg>(x).
    template < class Arg >
    auto identity( Arg&& x )
    {
        return Identity( std::forward< Arg >( x ) );
    }
} // namespace funcy
