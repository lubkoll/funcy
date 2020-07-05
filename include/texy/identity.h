#pragma once

#include <funcy/util/chainer.h>

#include <string>

namespace texy
{
    /// %Identity mapping \f$ f(x)=x \f$.
    struct Identity : funcy::Chainer< Identity >
    {
        /// Default constructor.
        Identity() = default;

        /**
         * @brief Constructor.
         * @param x point of evaluation.
         */
        Identity( const std::string& x )
        {
            update( x );
        }

        /// Reset point of evaluation
        void update( const std::string& x )
        {
            x_ = x;
        }

        /// Function value.
        const std::string& d0() const noexcept
        {
            return x_;
        }

        /// First directional derivative.
        template < int >
        const std::string& d1( const std::string& dx ) const noexcept
        {
            return dx;
        }

    private:
        std::string x_;
    };

    /// @return Identity(x).
    auto identity( const std::string& x )
    {
        return Identity( x );
    }
} // namespace texy
