#pragma once

#include <funcy/mathop/chain.h>
#include <funcy/util/chainer.h>

#include <texy/cmath/pow.h>
#include <texy/concepts.h>
#include <texy/util/string.h>
#include <type_traits>

namespace texy
{
    namespace linalg
    {
        /** @addtogroup TexifyLinearAlgebraGroup
         *   @{ */

        /// Compute squared Frobenius norm \f$ \|A\|^2 = A\negthinspace : \negthinspace A =
        /// \mathrm{tr}(A^TA) = \sum_{i,j} A_{ij}^2. \f$
        struct FrobeniusNormSquared : funcy::Chainer< FrobeniusNormSquared >
        {
            FrobeniusNormSquared() = default;

            explicit FrobeniusNormSquared( const std::string& A = "A" )
            {
                update( A );
            }

            /// Reset std::string to compute squared norm from.
            void update( const std::string& A )
            {
                A_ = A;
            }

            /// Squared std::string norm.
            auto d0() const noexcept
            {
                return std::string( "\\sum_{i,j}" ).append( addScope( A_ ) ).append( "_{ij}^2" );
            }

            /// First directional derivative.
            auto d1( const std::string& dA ) const
            {
                return std::string( "2\\sum_{i,j}(" )
                    .append( addScope( A_ ) )
                    .append( "_{ij}*" )
                    .append( addScope( dA ) )
                    .append( "_{ij})" );
            }

            /// Second directional derivative.
            auto d2( const std::string& dA, const std::string& dB ) const
            {

                return std::string( "2\\sum_{i,j}(" )
                    .append( addScope( dA ) )
                    .append( "_{ij}*" )
                    .append( addScope( dB ) )
                    .append( "_{ij})" );
            }

        private:
            std::string A_;
        };

        struct FrobeniusNorm : funcy::mathop::Chain< Pow< 1, 2 >, FrobeniusNormSquared >
        {
            FrobeniusNorm() = default;

            explicit FrobeniusNorm( const std::string& A = "A" )
                : funcy::mathop::Chain< Pow< 1, 2 >, FrobeniusNormSquared >(
                      Pow< 1, 2 >( "" ), FrobeniusNormSquared( A ) )
            {
                this->update( A );
            }
        };

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        inline auto frobenius_norm( const std::string& A )
        {
            return FrobeniusNorm( A );
        }

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < Function F >
        auto frobenius_norm( const F& f )
        {
            return FrobeniusNorm( f.d0() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace texy
