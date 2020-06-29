#pragma once

#include "dimension.h"
#include "rows_and_cols.h"

#include <funcy/concept_check.h>
#include <funcy/concepts.h>
#include <funcy/util/at.h>
#include <funcy/util/chainer.h>
#include <funcy/util/exceptions.h>
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
        namespace Detail
        {
            /// f Computes the trace of \f$A\f$, i.e. the sum of diagonal elements.
            template < int >
            struct ComputeTrace
            {
                template < SquareMatrix Matrix >
                static auto apply( const Matrix& A )
                {
                    auto val = at( A, 0, 0 );
                    for ( int i = 1; i < rows< Matrix >(); ++i )
                        val += at( A, i, i );
                    return val;
                }
            };

            /// Trace of 2x2-matrix.
            template <>
            struct ComputeTrace< 2 >
            {
                template < SquareMatrix Matrix >
                static auto apply( const Matrix& A )
                {
                    return at( A, 0, 0 ) + at( A, 1, 1 );
                }
            };

            /// Trace of a 3x3 matrix.
            template <>
            struct ComputeTrace< 3 >
            {
                template < SquareMatrix Matrix >
                static auto apply( const Matrix& A )
                {
                    return at( A, 0, 0 ) + at( A, 1, 1 ) + at( A, 2, 2 );
                }
            };
        } // namespace Detail

        /// %Trace of a matrix, i.e. sum of diagonal elements.
        template < SquareMatrix Matrix >
        struct ConstantSizeTrace : Chainer< ConstantSizeTrace< Matrix > >
        {
            ConstantSizeTrace() = default;

            /**
             * @brief Constructor.
             * @param A point of evaluation.
             */
            explicit ConstantSizeTrace( const Matrix& A )
            {
                update( A );
            }

            /// Reset point of evaluation.
            void update( const Matrix& A )
            {
                trace = Detail::ComputeTrace< dim< Matrix >() >::apply( A );
            }

            /// Function value.
            auto d0() const noexcept
            {
                return trace;
            }

            /// First directional derivative.
            auto d1( const Matrix& dA ) const
            {
                return Detail::ComputeTrace< dim< Matrix >() >::apply( dA );
            }

        private:
            std::decay_t< decltype(
                Detail::ComputeTrace< dim< Matrix >() >::apply( std::declval< Matrix >() ) ) >
                trace = 0;
        };

        /// %Trace of a matrix, i.e. sum of diagonal elements.
        template < class Matrix >
        struct DynamicSizeTrace : Chainer< DynamicSizeTrace< Matrix > >
        {
            DynamicSizeTrace() = default;

            /**
             * @brief Constructor.
             * @param A point of evaluation.
             */
            explicit DynamicSizeTrace( const Matrix& A )
            {
                update( A );
            }

            /// Reset point of evaluation.
            void update( const Matrix& A )
            {
#ifdef FUNCY_ENABLE_EXCEPTIONS
                if ( rows( A ) != cols( A ) )
                    throw NonSymmetricMatrixException( "DynamicSizeTrace", rows( A ), cols( A ),
                                                       __FILE__, __LINE__ );
#endif

                using Index = decltype( rows( std::declval< Matrix >() ) );
                trace = 0.;
                for ( Index i = 0; i < rows( A ); ++i )
                    trace += at( A, i, i );
            }

            /// Function value.
            auto d0() const noexcept
            {
                return trace;
            }

            /// First directional derivative.
            auto d1( const Matrix& dA ) const
            {
                using Index = decltype( rows( std::declval< Matrix >() ) );
                auto result = decltype( at( dA, 0, 0 ) )( 0. );
                for ( Index i = 0; i < rows( dA ); ++i )
                    result += at( dA, i, i );
                return result;
            }

        private:
            std::decay_t< decltype( at( std::declval< Matrix >(), 0, 0 ) ) > trace = 0;
        };
        /// @endcond

        /**
         * \brief Generate \f$\mathrm{tr}(A)\in\mathbb{R}^{n,n}\f$.
         * \param A matrix
         * \return Trace<Matrix>(A)
         */
        template < class Matrix, std::enable_if_t< !Concepts::isFunction< Matrix >() >* = nullptr >
        auto trace( const Matrix& A )
        {
            return DynamicSizeTrace< Matrix >( A );
        }

        /**
         * \brief Generate \f$\mathrm{tr}(A)\in\mathbb{R}^{n,n}\f$.
         * \param A matrix
         * \return Trace<Matrix>(A)
         */
        template < ConstantSize Matrix,
                   std::enable_if_t< !Concepts::isFunction< Matrix >() >* = nullptr >
        auto trace( const Matrix& A )
        {
            return ConstantSizeTrace< Matrix >( A );
        }

        /**
         * \brief Generate \f$\mathrm{tr}\circ f\f$, where \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$.
         * \param f function object mapping into a space of square matrices
         * \return Trace< std::decay_t<decltype(f())> >(f())( f )
         */
        template < Function F >
        auto trace( const F& f )
        {
            return trace( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace funcy
