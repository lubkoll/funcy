#pragma once

#include "rows_and_cols.h"

#include <funcy/cmath/pow.h>
#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
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
        namespace detail
        {
            template < ConstantSize M >
            inline auto computeScalarProduct( const M& A, const M& B )
            {
                using Index = decltype( rows< M >() );
                auto result = decltype( at( A, 0, 0 ) ){ 0. };
                for ( Index i = 0; i < rows< M >(); ++i )
                    for ( Index j = 0; j < cols< M >(); ++j )
                        result += at( A, i, j ) * at( B, i, j );
                return result;
            }

            template < class M >
            inline auto computeScalarProduct( const M& A, const M& B )
            {
                using Index = decltype( rows( A ) );
                auto result = decltype( at( A, 0, 0 ) ){ 0. };
                for ( Index i = 0; i < rows( A ); ++i )
                    for ( Index j = 0; j < cols( A ); ++j )
                        result += at( A, i, j ) * at( B, i, j );
                return result;
            }
        } // namespace detail
        /// @endcond

        /// Compute squared Frobenius norm \f$ \|A\|^2 = A\negthinspace : \negthinspace A =
        /// \mathrm{tr}(A^TA) = \sum_{i,j} A_{ij}^2. \f$
        template < class M >
        struct SquaredFrobeniusNorm : Chainer< SquaredFrobeniusNorm< M > >
        {
            SquaredFrobeniusNorm() = default;

            explicit SquaredFrobeniusNorm( const M& A ) : A_( A )
            {
                value = detail::computeScalarProduct( A_, A_ );
            }

            explicit SquaredFrobeniusNorm( M&& A ) : A_( std::move( A ) )
            {
                value = detail::computeScalarProduct( A_, A_ );
            }

            /// Reset matrix to compute squared norm from.
            void update( const M& A )
            {
                A_ = A;
                value = detail::computeScalarProduct( A_, A_ );
            }

            /// Squared matrix norm.
            auto d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            auto d1( const M& dA ) const
            {
                return 2 * detail::computeScalarProduct( A_, dA );
            }

            /// Second directional derivative.
            auto d2( const M& dA1, const M& dA2 ) const
            {
                return 2 * detail::computeScalarProduct( dA1, dA2 );
            }

        private:
            M A_;
            std::decay_t< decltype( at( std::declval< M >(), 0, 0 ) ) > value;
        };

        /// Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class M >
        using FrobeniusNorm = mathop::Chain< Sqrt, SquaredFrobeniusNorm< M > >;

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class M >
        auto frobeniusNorm( const M& A )
        {
            return FrobeniusNorm( A );
        }

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < Function F >
        auto frobeniusNorm( const F& f )
        {
            return FrobeniusNorm( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
