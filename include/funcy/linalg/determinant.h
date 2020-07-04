#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/dimension.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/linalg/type_traits.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>
#include <funcy/util/exceptions.h>
#include <funcy/util/static_checks.h>
#include <funcy/util/type_traits.h>

#include <type_traits>
#include <utility>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// @cond
        namespace detail
        {
            template < class Mat >
            inline auto compose_result( const Mat& A, const Mat& B )
            {
                return at( A, 0, 0 ) * at( B, 1, 1 ) + at( A, 1, 1 ) * at( B, 0, 0 ) -
                       ( at( A, 0, 1 ) * at( B, 1, 0 ) + at( A, 1, 0 ) * at( B, 0, 1 ) );
            }

            template < class Mat >
            inline auto compose_result( const Mat& dA, const Mat& dB, const Mat& dC )
            {
                return at( dB, 1, 1 ) *
                           ( at( dA, 0, 0 ) * at( dC, 2, 2 ) - at( dA, 2, 0 ) * at( dC, 0, 2 ) ) +
                       at( dB, 1, 2 ) *
                           ( at( dA, 0, 1 ) * at( dC, 2, 0 ) - at( dA, 2, 1 ) * at( dC, 0, 0 ) ) +
                       at( dB, 1, 0 ) *
                           ( at( dA, 0, 2 ) * at( dC, 2, 1 ) - at( dA, 2, 2 ) * at( dC, 0, 1 ) );
            }

            template < class Mat >
            inline auto compose_semi_symmetric_result( const Mat& dA, const Mat& dB, const Mat& dC )
            {
                return at( dB, 1, 1 ) *
                           ( at( dA, 0, 0 ) * at( dC, 2, 2 ) + at( dA, 2, 2 ) * at( dC, 0, 0 ) -
                             at( dA, 2, 0 ) * at( dC, 0, 2 ) - at( dA, 0, 2 ) * at( dC, 2, 0 ) ) +
                       at( dB, 1, 2 ) *
                           ( at( dA, 0, 1 ) * at( dC, 2, 0 ) + at( dA, 2, 0 ) * at( dC, 0, 1 ) -
                             at( dA, 2, 1 ) * at( dC, 0, 0 ) - at( dA, 0, 0 ) * at( dC, 2, 1 ) ) +
                       at( dB, 1, 0 ) *
                           ( at( dA, 0, 2 ) * at( dC, 2, 1 ) + at( dA, 2, 1 ) * at( dC, 0, 2 ) -
                             at( dA, 2, 2 ) * at( dC, 0, 1 ) - at( dA, 0, 1 ) * at( dC, 2, 2 ) );
            }

            template < class Mat, int dim = dim< Mat >() >
            class DeterminantImpl;

            template < class Mat >
            class DeterminantImpl< Mat, 2 > : public Chainer< DeterminantImpl< Mat, 2 > >
            {
            public:
                DeterminantImpl() = default;

                explicit DeterminantImpl( const Mat& A_ )
                {
                    update( A_ );
                }

                void update( const Mat& A_ )
                {
                    A = A_;
                    value = at( A, 0, 0 ) * at( A, 1, 1 ) - at( A, 0, 1 ) * at( A, 1, 0 );
                }

                auto d0() const
                {
                    return value;
                }

                auto d1( const Mat& dA1 ) const
                {
                    return compose_result( A, dA1 );
                }

                auto d2( const Mat& dA1, const Mat& dA2 ) const
                {
                    return compose_result( dA2, dA1 );
                }

            private:
                Mat A;
                std::decay_t< decltype( at( std::declval< Mat >(), 0, 0 ) ) > value = 0.;
            };

            template < class Mat >
            class DeterminantImpl< Mat, 3 > : public Chainer< DeterminantImpl< Mat, 3 > >
            {
            public:
                DeterminantImpl() = default;

                DeterminantImpl( const Mat& A_ )
                {
                    update( A_ );
                }

                void update( const Mat& A_ )
                {
                    A = A_;
                    value = compose_result( A, A, A );
                }

                auto d0() const
                {
                    return value;
                }

                auto d1( const Mat& dA1 ) const
                {
                    return compose_result( dA1, A, A ) + compose_result( A, dA1, A ) +
                           compose_result( A, A, dA1 );
                }

                auto d2( const Mat& dA1, const Mat& dA2 ) const
                {
                    return compose_semi_symmetric_result( A, dA2, dA1 ) +
                           compose_semi_symmetric_result( dA1, A, dA2 ) +
                           compose_semi_symmetric_result( A, dA1, dA2 );
                }

                auto d3( const Mat& dA1, const Mat& dA2, const Mat& dA3 ) const
                {
                    return compose_semi_symmetric_result( dA1, dA2, dA3 ) +
                           compose_semi_symmetric_result( dA1, dA3, dA2 ) +
                           compose_semi_symmetric_result( dA2, dA1, dA3 );
                }

            private:
                Mat A;
                std::decay_t< decltype( at( std::declval< Mat >(), 0, 0 ) ) > value = 0.;
            };
        } // namespace detail

        /// Determinant of constant size matrix with first three derivatives.
        template < class Mat >
        using ConstantSizeDeterminant = detail::DeterminantImpl< Mat >;

        /// Determinant of dynamic size matrix with first three derivatives.
        template < class Mat >
        class DynamicSizeDeterminant : public Chainer< DynamicSizeDeterminant< Mat > >
        {
        public:
            DynamicSizeDeterminant() = default;

            /// Constructor.
            DynamicSizeDeterminant( const Mat& A ) : dim( rows( A ) )
            {
                update( A );
            }

            /// Reset point of evaluation.
            void update( const Mat& A )
            {
#ifdef FUNCY_ENABLE_EXCEPTIONS
                if ( rows( A ) != cols( A ) )
                    throw NonSymmetricMatrixException( "DynamicSizeDeterminant", rows( A ),
                                                       cols( A ), __FILE__, __LINE__ );
#endif
                dim = rows( A );
                if ( dim == 2 )
                    det2D.update( A );
                if ( dim == 3 )
                    det3D.update( A );
            }

            /// Function value.
            auto d0() const
            {
                return ( dim == 2 ) ? det2D() : det3D();
            }

            /// First (directional) derivative.
            auto d1( const Mat& dA1 ) const
            {
                return ( dim == 2 ) ? det2D.d1( dA1 ) : det3D.d1( dA1 );
            }

            /// Second (directional) derivative.
            auto d2( const Mat& dA1, const Mat& dA2 ) const
            {
                return ( dim == 2 ) ? det2D.d2( dA1, dA2 ) : det3D.d2( dA1, dA2 );
            }

            /// Third (directional) derivative.
            auto d3( const Mat& dA1, const Mat& dA2, const Mat& dA3 ) const
            {
                return ( dim == 2 ) ? 0 : det3D.d3( dA1, dA2, dA3 );
            }

        private:
            int dim = 0;
            detail::DeterminantImpl< Mat, 2 > det2D;
            detail::DeterminantImpl< Mat, 3 > det3D;
        };
        /// @endcond

        /**
         * @brief Generate \f$\det(A)\f$.
         * @param A square matrix
         * @return Determinant<Matrix>(A)
         */
        template < class Mat >
        auto det( const Mat& A ) requires( !Function< Mat > && !SquareMatrix< Mat > )
        {
            return DynamicSizeDeterminant( A );
        }

        /**
         * @brief Generate \f$\det(A)\f$.
         * @param A square matrix
         * @return Determinant<Matrix>(A)
         */
        template < SquareMatrix Mat >
        auto det( const Mat& A )
        {
            return ConstantSizeDeterminant< Mat >( A );
        }

        /**
         * @brief Generate \f$\det\circ f\f$.
         * @param f function mapping into a space of square matrices
         * @return Determinant< std::decay_t<decltype(f())> >(f())(f)
         */
        template < Function F >
        auto det( const F& f )
        {
            return det( f() )( f );
        }

        /** @} */
    } // namespace linalg
} // namespace funcy
