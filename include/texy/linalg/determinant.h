#pragma once

#include "cofactor.h"
#include "trace.h"
#include "transpose.h"

#include <texy/constant.h>
#include <texy/util/chainer.h>
#include <texy/util/string.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>

#include <type_traits>
#include <utility>

namespace texy
{
    namespace linalg
    {
        /** @addtogroup TexifyLinearAlgebraGroup
         *  @{ */
        class Determinant : public Chainer< Determinant >
        {
        public:
            Determinant() = default;

            /// Constructor.
            Determinant( const std::string& A = "A" ) : A( A )
            {
                update( A );
            }

            /// Reset point of evaluation.
            void update( const std::string& A )
            {
                this->A = A;
            }

            /// Function value.
            std::string d0() const
            {
                return std::string( "\\det" ).append( forceAddScope( A ) );
            }

            /// First (directional) derivative.
            std::string d1( const std::string& dA ) const
            {
                return trace( transpose( cof( A ) )().append( "*" ).append( addScope( dA ) ) )();
            }

            /// Second (directional) derivative.
            std::string d2( const std::string& dA, const std::string& dB ) const
            {
                return trace( transpose( cof( A ).d1( addScope( dB ) ) )().append( "*" ).append(
                    addScope( dA ) ) )();
            }

            /// Third (directional) derivative.
            std::string d3( const std::string& dA, const std::string& dB,
                            const std::string& dC ) const
            {
                return trace( transpose( cof( A ).d2( addScope( dB ), addScope( dC ) ) )()
                                  .append( "*" )
                                  .append( addScope( dA ) ) )();
            }

        private:
            std::string A;
        };

        /**
         * @brief Generate \f$\det(A)\f$.
         * @param A square matrix
         * @return Determinant(A)
         */
        inline auto det( const std::string& A )
        {
            return Determinant( A );
        }

        /**
         * @brief Generate \f$\det\circ f\f$.
         * @param f function mapping into a space of square matrices
         * @return Determinant< std::decay_t<decltype(f.d0())> >(f.d0())(f)
         */
        template < class F, std::enable_if_t< funcy::Concepts::isFunction< F >() >* = nullptr >
        auto det( const F& f )
        {
            return Determinant( f.d0() )( f );
        }
        /** @} */
    }
}
