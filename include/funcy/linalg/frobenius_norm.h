#pragma once

#include <funcy/cmath/pow.h>
#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>

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
            template < ConstantSize Mat >
            [[nodiscard]] inline auto compute_scalar_product( const Mat& A, const Mat& B )
            {
                using Index = decltype( rows< Mat >() );
                auto result = decltype( at( A, 0, 0 ) ){ 0. };
                for ( Index i = 0; i < rows< Mat >(); ++i )
                    for ( Index j = 0; j < cols< Mat >(); ++j )
                        result += at( A, i, j ) * at( B, i, j );
                return result;
            }

            template < class Mat >
            [[nodiscard]] inline auto compute_scalar_product( const Mat& A, const Mat& B )
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
        template < class Mat >
        struct SquaredFrobeniusNorm : Chainer< SquaredFrobeniusNorm< Mat > >
        {
            SquaredFrobeniusNorm() = default;

            explicit SquaredFrobeniusNorm( const Mat& A ) : A_( A )
            {
                value = detail::compute_scalar_product( A_, A_ );
            }

            explicit SquaredFrobeniusNorm( Mat&& A ) : A_( std::move( A ) )
            {
                value = detail::compute_scalar_product( A_, A_ );
            }

            /// Reset matrix to compute squared norm from.
            void update( const Mat& A )
            {
                A_ = A;
                value = detail::compute_scalar_product( A_, A_ );
            }

            /// Squared matrix norm.
            [[nodiscard]] auto d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            [[nodiscard]] auto d1( const Mat& dA ) const
            {
                return 2 * detail::compute_scalar_product( A_, dA );
            }

            /// Second directional derivative.
            [[nodiscard]] auto d2( const Mat& dA1, const Mat& dA2 ) const
            {
                return 2 * detail::compute_scalar_product( dA1, dA2 );
            }

        private:
            Mat A_;
            std::decay_t< decltype( at( std::declval< Mat >(), 0, 0 ) ) > value;
        };

        /// Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class Mat >
        using FrobeniusNorm = mathop::Chain< Sqrt, SquaredFrobeniusNorm< Mat > >;

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < class Mat >
        [[nodiscard]] auto frobenius_norm( const Mat& A )
        {
            return FrobeniusNorm( A );
        }

        /// Generate Frobenius norm \f$ \|A\| = \sqrt{A\negthinspace : \negthinspace A }=
        /// \sqrt{\mathrm{tr}(A^TA)} = \sqrt{\sum_{i,j} A_{ij}^2}. \f$
        template < Function F >
        [[nodiscard]] auto frobenius_norm( const F& f )
        {
            return FrobeniusNorm( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
