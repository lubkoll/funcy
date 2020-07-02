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

            template < int row, Matrix M >
            auto symmetricCofactorDerivative( const M& A, const M& dA )
            {
                return computeCofactorDirectionalDerivative< row, row >( A, dA ) +
                       computeCofactorDirectionalDerivative< row, row >( dA, A );
            }

            template < int >
            struct Compute;

            template <>
            struct Compute< 2 >
            {
                template < Matrix M >
                static auto sumOfDiagonalCofactors( const M& A )
                {
                    return computeCofactor< 0, 0 >( A ) + computeCofactor< 1, 1 >( A );
                }

                template < Matrix M >
                static auto sumOfSymmetricCofactorDerivatives( const M& A, const M& B )
                {
                    return symmetricCofactorDerivative< 0 >( A, B ) +
                           symmetricCofactorDerivative< 1 >( A, B );
                }
            };

            template <>
            struct Compute< 3 >
            {
                template < Matrix M >
                static auto sumOfDiagonalCofactors( const M& A )
                {
                    return computeCofactor< 0, 0 >( A ) + computeCofactor< 1, 1 >( A ) +
                           computeCofactor< 2, 2 >( A );
                }

                template < Matrix M >
                static auto sumOfSymmetricCofactorDerivatives( const M& A, const M& B )
                {
                    return symmetricCofactorDerivative< 0 >( A, B ) +
                           symmetricCofactorDerivative< 1 >( A, B ) +
                           symmetricCofactorDerivative< 2 >( A, B );
                }
            };

            /// Fallback implementation if matrix size can not be determined at compile time.
            template <>
            struct Compute< -1 >
            {
                template < Matrix M >
                static auto sumOfDiagonalCofactors( const M& A )
                {
                    if ( rows( A ) == 2 )
                        return Compute< 2 >::sumOfDiagonalCofactors( A );
                    /*if(rows(A) == 3)*/ return Compute< 3 >::sumOfDiagonalCofactors( A );
                }

                template < Matrix M >
                static auto sumOfSymmetricCofactorDerivatives( const M& A, const M& B )
                {
                    if ( rows( A ) == 2 )
                        return Compute< 2 >::sumOfSymmetricCofactorDerivatives( A, B );
                    /*if(rows(A) == 3)*/ return Compute< 3 >::sumOfSymmetricCofactorDerivatives(
                        A, B );
                }
            };
        } // namespace detail
        /// @endcond

        /** @addtogroup InvariantGroup, LinearAlgebraGroup
         * @{ */
        /// Second principal invariant \f$ \iota_2(A)=\mathrm{tr}(\mathrm{cof}(A)) \f$ for
        /// \f$A\in\mathbb{R}^{n,n}\f$.
        template < Matrix M >
        class SecondPrincipalInvariant : public Chainer< SecondPrincipalInvariant< M > >
        {
        public:
            SecondPrincipalInvariant() = default;

            /**
             * @brief Constructor.
             * @param A matrix to compute second principal invariant from
             */
            SecondPrincipalInvariant( const M& A )
            {
                update( A );
            }

            /// Reset matrix to compute second principal invariant from.
            void update( const M& A )
            {
                if ( !initialized )
                {
                    new ( &A_ ) M{ A };
                    initialized = true;
                }
                else
                    A_ = A;
                value = detail::Compute< dim< M >() >::sumOfDiagonalCofactors( A );
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
            auto d1( const M& dA1 ) const
            {
                return detail::Compute< dim< M >() >::sumOfSymmetricCofactorDerivatives( A_, dA1 );
            }

            /**
             * @brief Second directional derivative
             * @param dA1 direction for which the derivative is computed
             * @param dA2 direction for which the derivative is computed
             */
            auto d2( const M& dA1, const M& dA2 ) const
            {
                return detail::Compute< dim< M >() >::sumOfSymmetricCofactorDerivatives( dA1, dA2 );
            }

        private:
            M A_;
            std::decay_t< decltype( at( std::declval< M >(), 0, 0 ) ) > value = 0;
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
