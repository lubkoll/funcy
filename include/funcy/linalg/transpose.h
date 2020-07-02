#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>
#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/zero.h>

#include <concepts>
#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /// @cond
        namespace detail
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

            template < ConstantSize Mat >
            Transposed_t< Mat >
            transpose( Mat A ) requires( !std::same_as< Mat, Transposed_t< Mat > > )
            {
                auto a = at( A, 0, 0 );
                for ( int i = 0; i < rows< Mat >(); ++i )
                    for ( int j = i + 1; j < cols< Mat >(); ++j )
                    {
                        a = at( A, i, j );
                        at( A, i, j ) = at( A, j, i );
                        at( A, j, i ) = a;
                    }

                return A;
            }

            /// Compute transpose of non-square matrix.
            template < ConstantSize Mat >
            Transposed_t< Mat >
            transpose( const Mat& A ) requires( !std::same_as< Mat, Transposed_t< Mat > > )
            {
                auto B = zero< Transposed_t< Mat > >();
                for ( int i = 0; i < rows< Mat >(); ++i )
                    for ( int j = 0; j < cols< Mat >(); ++j )
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
        } // namespace detail
        /// @endcond

        /** @addtogroup LinearAlgebraGroup
         *  @{ */
        template < class Mat >
        class Transpose : public Chainer< Transpose< Mat > >
        {
        public:
            explicit Transpose( const Mat& A )
            {
                AT_ = detail::transpose( A );
            }

            void update( const Mat& A )
            {
                AT_ = detail::transpose( A );
            }

            const auto& d0() const noexcept
            {
                return AT_;
            }

            auto d1( const Mat& dA ) const
            {
                return detail::transpose( dA );
            }

        private:
            typename detail::WrappedMatrix< Mat >::type AT_;
        };

        /**
         * @brief Generate \f$A^T\in\mathbb{R}^{n,n}\f$.
         * \param A square matrix
         * \return Transpose<Matrix>(A)
         */
        template < class Mat >
        auto transpose( const Mat& A )
        {
            return Transpose< Mat >( A );
        }

        /**
         * @brief Generate \f$f^T\f$, where \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$.
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
