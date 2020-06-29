#pragma once

#include "rows_and_cols.h"

#include <funcy/cmath/pow.h>
#include <funcy/concept_check.h>
#include <funcy/concepts.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>
#include <funcy/util/static_checks.h>

#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *   @{ */

        /// @cond
        namespace FrobeniusDetail
        {
            template < ConstantSize Matrix >
            inline auto computeScalarProduct( const Matrix& A, const Matrix& B )
            {
                using Index = decltype( rows< Matrix >() );
                auto result = decltype( at( A, 0, 0 ) ){ 0. };
                for ( Index i = 0; i < rows< Matrix >(); ++i )
                    for ( Index j = 0; j < cols< Matrix >(); ++j )
                        result += at( A, i, j ) * at( B, i, j );
                return result;
            }

            template < class Matrix >
            inline auto computeScalarProduct( const Matrix& A, const Matrix& B )
            {
                using Index = decltype( rows( A ) );
                auto result = decltype( at( A, 0, 0 ) ){ 0. };
                for ( Index i = 0; i < rows( A ); ++i )
                    for ( Index j = 0; j < cols( A ); ++j )
                        result += at( A, i, j ) * at( B, i, j );
                return result;
            }
        } // namespace FrobeniusDetail
        /// @endcond

        /// Compute squared Frobenius norm \f$ \|A\|^2 = A\negthinspace : \negthinspace A =
        /// \mathrm{tr}(A^TA) = \sum_{i,j} A_{ij}^2. \f$
        template < class Matrix, class = Concepts::IsMatrix< Matrix > >
        struct SquaredFrobeniusNorm : Chainer< SquaredFrobeniusNorm< Matrix > >
        {
            SquaredFrobeniusNorm() = default;

            explicit SquaredFrobeniusNorm( const Matrix& A )
            {
                update( A );
            }

            /// Reset matrix to compute squared norm from.
            void update( const Matrix& A )
            {
                A_ = A;
                value = FrobeniusDetail::computeScalarProduct( A_, A_ );
            }

            /// Squared matrix norm.
            auto d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            auto d1( const Matrix& dA ) const
            {
                return 2 * FrobeniusDetail::computeScalarProduct( A_, dA );
            }

            /// Second directional derivative.
            auto d2( const Matrix& dA1, const Matrix& dA2 ) const
            {
                return 2 * FrobeniusDetail::computeScalarProduct( dA1, dA2 );
            }

        private:
            Matrix A_;
            std::decay_t< decltype( at( std::declval< Matrix >(), 0, 0 ) ) > value;
        };

        /// Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class Matrix >
        using FrobeniusNorm = mathop::Chain< Sqrt, SquaredFrobeniusNorm< Matrix > >;

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class Matrix >
        auto frobeniusNorm( const Matrix& A )
        {
            return FrobeniusNorm< Matrix >( A );
        }

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < Function F >
        auto frobeniusNorm( const F& f )
        {
            return FrobeniusNorm< std::decay_t< decltype( f() ) > >( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
