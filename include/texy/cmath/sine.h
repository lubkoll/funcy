#pragma once

#include <funcy/util/chainer.h>

#include <texy/concepts.h>
#include <texy/util/string.h>

/*!
  @ingroup TexifyCMathGroup

  @brief Sine function (based on sin(double) in \<cmath\>).

  For scalar functions directional derivatives are less interesting. Incorporating this function
  as building block for more complex functions requires directional derivatives. These occur
  during applications of the chain rule.
 */
namespace texy
{
    struct Sin : funcy::Chainer< Sin >
    {
        //! @copydoc Cos::Cos()
        explicit Sin( std::string x = "x" )
        {
            update( x );
        }

        //! @copydoc Cos::update()
        void update( const std::string& x )
        {
            this->x = addTexScope( forceAddScope( x ) );
        }

        //! @copydoc Cos::d0()
        std::string d0() const noexcept
        {
            return std::string( R"(\sin)" ).append( x );
        }

        //! @copydoc Cos::d1()
        std::string d1( const std::string& dx = "" ) const
        {
            return std::string( R"(\cos)" ).append( x ).append( multiply_if_not_empty( dx ) );
        }

        //! @copydoc Cos::d2()
        std::string d2( const std::string& dx = "", const std::string& dy = "" ) const
        {
            return std::string( R"(-\sin)" ).append( x ).append( multiply_if_not_empty( dx, dy ) );
        }

        //! @copydoc Cos::d3()
        std::string d3( const std::string& dx = "", const std::string& dy = "",
                        const std::string& dz = "" ) const
        {
            return std::string( R"(-\cos)" )
                .append( x )
                .append( multiply_if_not_empty( dx, dy, dz ) );
        }

    private:
        std::string x;
    };

    /*!
      @ingroup TexifyCMathGroup
      @brief Generate \f$ \sin\circ f \f$.
      @param f function mapping into a scalar space
      @return object of type mathop::Chain<Sin,Function>
     */
    template < Function F >
    auto sin( const F& f )
    {
        return Sin()( f );
    }
} // namespace texy
