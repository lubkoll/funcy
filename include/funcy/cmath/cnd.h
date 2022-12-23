#pragma once

#include <funcy/concepts.h>
#include <funcy/util/chainer.h>

#include <cmath>

namespace funcy
{
    /*!
      @ingroup CMathGroup

      @brief Cumulative standard normal distribution.

      For scalar functions directional derivatives are less interesting. Incorporating this function
      as building block for more complex functions requires directional derivatives. These occur
      during applications of the chain rule.
     */
    struct CumulativeNormalDistribution : Chainer< CumulativeNormalDistribution >
    {
        /**
         * @brief Constructor.
         * @param x point of evaluation
         */
        explicit CumulativeNormalDistribution( double x = 0. ) noexcept
        {
            update( x );
        }

        /// Set point of evaluation.
        void update( double x ) noexcept
        {
            x_ = x;
            value_ = 0.5 * ( 1 + std::erf( x_ * div_sqrt2 ) );
            d1_ = std::exp( -0.5 * x_ * x_ );
        }

        /// Function value.
        [[nodiscard]] double d0() const noexcept
        {
            return value_;
        }

        /// First (directional) derivative.
        [[nodiscard]] double d1( double dx = 1. ) const noexcept
        {
            return div_sqrt2pi * d1_ * dx;
        }

        /// Second (directional) derivative.
        [[nodiscard]] double d2( double dx = 1., double dy = 1. ) const noexcept
        {
            return -div_sqrt2pi * x_ * d1_ * dx * dy;
        }

        /// Third (directional) derivative.
        [[nodiscard]] double d3( double dx = 1., double dy = 1., double dz = 1. ) const noexcept
        {
            return div_sqrt2pi * ( -d1_ + x_ * x_ * d1_ ) * dx * dy * dz;
        }

    private:
        static const double div_sqrt2;
        static const double div_sqrt2pi;
        double value_;
        double d1_;
        double x_;
    };

    inline const double CumulativeNormalDistribution::div_sqrt2 = 1 / std::sqrt( 2 );
    inline const double CumulativeNormalDistribution::div_sqrt2pi = 1 / std::sqrt( 2 * M_PI );

    [[nodiscard]] inline auto cnd( double x )
    {
        return CumulativeNormalDistribution( x )();
    }

    /*!
      @ingroup CMathGroup
      @brief Generate \f$ \mathrm{cnd}\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<CumulativeNormalDistribution,Function>
     */
    template < Function F >
    [[nodiscard]] auto cnd( const F& f )
    {
        return CumulativeNormalDistribution()( f );
    }
} // namespace funcy
