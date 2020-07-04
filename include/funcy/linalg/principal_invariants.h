#pragma once

#include "cofactor.h"
#include "determinant.h"
#include "dimension.h"
#include "trace.h"

#include <funcy/cmath/pow.h>
#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/util/chainer.h>
#include <funcy/util/type_traits.h>

#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /// @cond
        namespace detail
        {

            template < int row, Matrix Mat >
            auto symmetric_cofactor_derivative( const Mat& A, const Mat& dA )
            {
                return compute_cofactor_directional_derivative< row, row >( A, dA ) +
                       compute_cofactor_directional_derivative< row, row >( dA, A );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_diagonal_cofactors( const Mat& A ) requires( dim == 2 )
            {
                return linalg::compute_cofactor< 0, 0 >( A ) +
                       linalg::compute_cofactor< 1, 1 >( A );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_symmetric_cofactor_derivatives( const Mat& A,
                                                               const Mat& B ) requires( dim == 2 )
            {
                return symmetric_cofactor_derivative< 0 >( A, B ) +
                       symmetric_cofactor_derivative< 1 >( A, B );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_diagonal_cofactors( const Mat& A ) requires( dim == 3 )
            {
                return linalg::compute_cofactor< 0, 0 >( A ) +
                       linalg::compute_cofactor< 1, 1 >( A ) +
                       linalg::compute_cofactor< 2, 2 >( A );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_symmetric_cofactor_derivatives( const Mat& A,
                                                               const Mat& B ) requires( dim == 3 )
            {
                return symmetric_cofactor_derivative< 0 >( A, B ) +
                       symmetric_cofactor_derivative< 1 >( A, B ) +
                       symmetric_cofactor_derivative< 2 >( A, B );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_diagonal_cofactors( const Mat& A ) requires( dim == -1 )
            {
                if ( rows( A ) == 2 )
                    return sum_of_diagonal_cofactors< 2 >( A );
                /*if(rows(A) == 3)*/ return sum_of_diagonal_cofactors< 3 >( A );
            }

            template < int dim, Matrix Mat >
            static auto sum_of_symmetric_cofactor_derivatives( const Mat& A,
                                                               const Mat& B ) requires( dim == -1 )
            {
                if ( rows( A ) == 2 )
                    return sum_of_symmetric_cofactor_derivatives< 2 >( A, B );
                /*if(rows(A) == 3)*/ return sum_of_symmetric_cofactor_derivatives< 3 >( A, B );
            }
        } // namespace detail
        /// @endcond

        /** @addtogroup InvariantGroup, LinearAlgebraGroup
         * @{ */
        /// Second principal invariant \f$ \iota_2(A)=\mathrm{tr}(\mathrm{cof}(A)) \f$ for
        /// \f$A\in\mathbb{R}^{n,n}\f$.
        template < Matrix Mat >
        class SecondPrincipalInvariant : public Chainer< SecondPrincipalInvariant< Mat > >
        {
        public:
            SecondPrincipalInvariant() = default;

            /**
             * @brief Constructor.
             * @param A matrix to compute second principal invariant from
             */
            SecondPrincipalInvariant( const Mat& A )
            {
                update( A );
            }

            /// Reset matrix to compute second principal invariant from.
            void update( const Mat& A )
            {
                if ( !initialized )
                {
                    new ( &A_ ) Mat{ A };
                    initialized = true;
                }
                else
                    A_ = A;
                value = detail::sum_of_diagonal_cofactors< dim< Mat >() >( A );
            }

            /// Value of the second principal invariant
            auto d0() const
            {
                return value;
            }

            /**
             * @brief First directional derivative
             * @param dA1 direction for which the derivative is computed
             */
            auto d1( const Mat& dA1 ) const
            {
                return detail::sum_of_symmetric_cofactor_derivatives< dim< Mat >() >( A_, dA1 );
            }

            /**
             * @brief Second directional derivative
             * @param dA1 direction for which the derivative is computed
             * @param dA2 direction for which the derivative is computed
             */
            auto d2( const Mat& dA1, const Mat& dA2 ) const
            {
                return detail::sum_of_symmetric_cofactor_derivatives< dim< Mat >() >( dA1, dA2 );
            }

        private:
            Mat A_;
            std::decay_t< decltype( at( std::declval< Mat >(), 0, 0 ) ) > value = 0;
            bool initialized = false;
        };

        /**
         * @brief Generate first principal invariant.
         *
         * Depending on the argument either generates \f$\mathrm{tr}(A)\f$ or \f$\mathrm{tr}\circ
         * f\f$.
         *
         * @return if x is a matrix then the this functions returns Trace<Arg>(x), if x is a
         * function, then it returns
         * Trace< std::decay_t<decltype(x())> >( x() )( x );
         */
        template < class Arg >
        auto i1( Arg&& x )
        {
            return trace( std::forward< Arg >( x ) );
        }

        /**
         * @brief Convenient generation of second principal invariant \f$
         * \iota_2(A)=\mathrm{tr}(\mathrm{cof}(A)) \f$ for \f$A\in\mathbb{R}^{n,n}\f$.
         * @return SecondPrincipalInvariant<Matrix>(A)
         */
        template < Matrix M >
        auto i2( M&& A )
        {
            return SecondPrincipalInvariant( std::forward< M >( A ) );
        }

        /**
         * @brief Convenient generation of second principal invariant \f$ \iota_2\circ f \f$ for
         * \f$f:\cdot\mapsto\mathbb{R}^{n,n}\f$.
         * @return SecondPrincipalInvariant( f() )( f )
         */
        template < Function F >
        auto i2( const F& f )
        {
            return SecondPrincipalInvariant( f() )( f );
        }

        /**
         * @brief Generate third principal invariant.
         *
         * Depending on the argument either generates \f$\det(A)\f$ or \f$\det\circ f\f$.
         *
         * @return if x is a matrix then the this functions returns Determinant<Arg>(x), if x is a
         * function, then it returns
         * Determinant< std::decay_t<decltype(x())> >( x() )( x );
         */
        template < class Arg >
        auto i3( const Arg& x )
        {
            return det( x );
        }

        /**
         * @brief Isochoric (volume-preserving), first modified principal invariant \f$
         * \bar\iota_1(A)=\iota_1\iota_3^{-1/3} \f$, where \f$\iota_1\f$ is the first
         * and \f$\iota_3\f$ is the third principal invariant.
         * @param x either a square matrix or a function returning a square matrix
         */
        template < class Arg, int n = dim< Arg >() >
        auto mi1( const Arg& x )
        {
            return i1( x ) * pow< -1, n >( det( x ) );
        }

        /**
         * @brief Isochoric (volume-preserving), second modified principal invariant \f$
         * \bar\iota_2(A)=\iota_2\iota_3^{-2/3} \f$, where \f$\iota_2\f$ is the second
         * and \f$\iota_3\f$ is the third principal invariant.
         * @param x either a square matrix or a function returning a square matrix
         */
        template < class Arg, int n = dim< Arg >() >
        auto mi2( const Arg& x )
        {
            return i2( x ) * pow< -2, n >( det( x ) );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
