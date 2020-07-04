#pragma once

#include <funcy/util/chainer.h>

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
        Identity( const Arg& x )
        {
            update( x );
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
    auto identity( const Arg& x )
    {
        return Identity< Arg >( x );
    }
} // namespace funcy
