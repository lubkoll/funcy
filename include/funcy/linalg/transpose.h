#pragma once

#include "funcy/concept_check.h"
#include "rows_and_cols.h"

#include <funcy/concepts.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>
#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/zero.h>

#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /// @cond
        namespace Detail
        {
            template < class M >
            struct WrappedMatrix
            {
                using type = M;
            };

            template < ConstantSize M >
            struct WrappedMatrix< M >
            {
                using type = typename GetTransposed< M >::type;
            };

            template <
                ConstantSize Matrix,
                ConstantSize TransposedMatrix = typename GetTransposed< Matrix >::type,
                std::enable_if_t< std::is_same< Matrix, TransposedMatrix >::value >* = nullptr >
            TransposedMatrix transpose( Matrix A )
            {
                auto a = at( A, 0, 0 );
                for ( int i = 0; i < rows< Matrix >(); ++i )
                    for ( int j = i + 1; j < cols< Matrix >(); ++j )
                    {
                        a = at( A, i, j );
                        at( A, i, j ) = at( A, j, i );
                        at( A, j, i ) = a;
                    }

                return A;
            }

            /// Compute transpose of non-square matrix.
            template <
                ConstantSize Matrix, ConstantSize TransposedMatrix = Transposed_t< Matrix >,
                std::enable_if_t< !std::is_same< Matrix, TransposedMatrix >::value >* = nullptr >
            TransposedMatrix transpose( const Matrix& A )
            {
                TransposedMatrix B = zero< TransposedMatrix >();
                for ( int i = 0; i < rows< Matrix >(); ++i )
                    for ( int j = 0; j < cols< Matrix >(); ++j )
                        at( B, j, i ) = A( i, j );
                return B;
            }

            /// Compute transpose of square matrix.
            template < class Matrix >
            Matrix transpose( Matrix A )
            {
                assert( rows( A ) == cols( A ) );
                using Index = decltype( rows( std::declval< Matrix >() ) );
                auto a = std::decay_t< decltype( at( A, 0, 0 ) ) >( 0. );
                for ( Index i = 0; i < rows( A ); ++i )
                    for ( Index j = i + 1; j < cols( A ); ++j )
                    {
                        a = at( A, i, j );
                        at( A, i, j ) = at( A, j, i );
                        at( A, j, i ) = a;
                    }

                return A;
            }
        } // namespace Detail
        /// @endcond

        /** @addtogroup LinearAlgebraGroup
         *  @{ */
        template < class Matrix, class = Concepts::IsMatrix< Matrix > >
        class Transpose;

        /// Represents transposition of constant-size matrices.
        template < class Matrix >
        class Transpose< Matrix, Concepts::IsMatrix< Matrix > >
            : public Chainer< Transpose< Matrix, Concepts::IsMatrix< Matrix > > >
        {
        public:
            explicit Transpose( const Matrix& A )
            {
                AT_ = Detail::transpose( A );
            }

            void update( const Matrix& A )
            {
                AT_ = Detail::transpose( A );
            }

            const auto& d0() const noexcept
            {
                return AT_;
            }

            auto d1( const Matrix& dA ) const
            {
                return Detail::transpose( dA );
            }

        private:
            typename Detail::WrappedMatrix< Matrix >::type AT_;
        };

        /**
         * \brief Generate \f$A^T\in\mathbb{R}^{n,n}\f$.
         * \param A square matrix
         * \return Transpose<Matrix>(A)
         */
        template < class Matrix >
        auto transpose( const Matrix& A )
        {
            return Transpose< Matrix >( A );
        }

        /**
         * \brief Generate \f$f^T\f$, where \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$.
         * \param f function object mapping into a space of square matrices
         * \return Transpose< decay_t<decltype(f())> >(f())( f )
         */
        template < Function F >
        auto transpose( const F& f )
        {
            return Transpose< decay_t< decltype( f() ) > >( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
