#pragma once

#include <funcy/util/chainer.h>

#include <cmath>
#include <texy/concepts.h>
#include <texy/util/string.h>

/*!
  @ingroup TexifyCMathGroup

  @brief Cosine function (based on cos(double) in \<cmath\>).

  For scalar functions directional derivatives are less interesting. Incorporating this function
  as building block for more complex functions requires directional derivatives. These occur
  during applications of the chain rule.
 */
namespace texy
{
    struct Cos : funcy::Chainer< Cos >
    {
        /**
         * @brief Constructor.
         * @param x point of evaluation
         */
        explicit Cos( std::string x = "x" )
        {
            update( x );
        }

        /// Set point of evaluation.
        void update( const std::string& x )
        {
            this->x = addTexScope( forceAddScope( x ) );
        }

        /// Function value.
        std::string d0() const noexcept
        {
            return std::string( "\\cos" ).append( x );
        }

        /// First (directional) derivative.
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( "-\\sin" ).append( x ).append( multiply_if_not_empty( dx ) );
        }

        /// Second (directional) derivative.
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( "-\\cos" ).append( x ).append( multiply_if_not_empty( dx, dy ) );
        }

        /// Third (directional) derivative.
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( "\\sin" ).append( x ).append( multiply_if_not_empty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    /*!
      @ingroup TexifyCMathGroup
      @brief Generate \f$ \cos\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Cosc,Function>
     */
    template < Function F >
    auto cos( const F& f )
    {
        return Cos()( f );
    }
} // namespace texy
