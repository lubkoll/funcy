#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/dimension.h>
#include <funcy/util/at.h>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// @cond
        namespace detail
        {
            constexpr int getFirst( int row )
            {
                return ( row == 0 ) ? 1 : 0;
            }

            constexpr int getLast( int row )
            {
                return ( row == 2 ) ? 1 : 2;
            }

            template < int row, int col >
            struct CofactorIndices
            {
                static constexpr int firstRow = getFirst( row );
                static constexpr int lastRow = getLast( row );
                static constexpr int firstCol = getFirst( col );
                static constexpr int lastCol = getLast( col );
            };

            constexpr int sign( int row, int col )
            {
                return ( ( ( row + col ) % 2 == 0 ) ? 1 : -1 );
            }

            template < int row, int col, int dim, SquareMatrix Matrix >
            auto computeCofactorImpl( const Matrix&, Matrix const& A ) requires( dim == 2 )
            {
                using Id = detail::CofactorIndices< row, col >;
                return sign( row, col ) * at( A, Id::firstRow, Id::firstCol );
            }

            template < int row, int col, int dim, SquareMatrix Matrix >
            auto computeCofactorImpl( const Matrix& A, const Matrix& B ) requires( dim == 3 )
            {
                using Id = detail::CofactorIndices< row, col >;
                return sign( row, col ) *
                       ( at( A, Id::firstRow, Id::firstCol ) * at( B, Id::lastRow, Id::lastCol ) -
                         at( A, Id::firstRow, Id::lastCol ) * at( B, Id::lastRow, Id::firstCol ) );
            }
        } // namespace detail
        /// @endcond

        /**
         * @brief Compute the \f$(row,col)\f$-cofactor of \f$ A \f$. Implemented for \f$ A\in
         * \mathbb{R}^{n,n} \f$ with \f$ n=2,3 \f$.
         *
         * The \f$(i,j)\f$-cofactor of a matrix \f$ A \f$ is \f$ (-1)^{i+j} \det(A^\#_{ij}) \f$,
         * where \f$ A^\#_ij \f$ is obtained from \f$ A \f$ by deleting the \f$i\f$-th row and \f$ j
         * \f$-th column.
         */
        template < int row, int col, ConstantSize Matrix >
        auto computeCofactor( Matrix const& A )
        {
            static_assert( dim< Matrix >() == 2 || dim< Matrix >() == 3,
                           "Cofactors are currently only implemented for 2x2 and 3x3 matrices. "
                           "Efficient general implementations are non-trivial and may or may not "
                           "be implemented in the future." );
            return detail::computeCofactorImpl< row, col, dim< Matrix >() >( A, A );
        }

        /**
         * @brief Compute the \f$(row,col)\f$-cofactor of \f$ A \f$. Implemented for \f$ A\in
         * \mathbb{R}^{n,n} \f$ with \f$ n=2,3 \f$.
         *
         * The \f$(i,j)\f$-cofactor of a matrix \f$ A \f$ is \f$ (-1)^{i+j} \det(A^\#_{ij}) \f$,
         * where \f$ A^\#_ij \f$ is obtained from \f$ A \f$ by deleting the \f$i\f$-th row and \f$ j
         * \f$-th column.
         */
        template < int row, int col, class Matrix >
        auto computeCofactor( Matrix const& A )
        {
            assert( ( rows( A ) == 2 && cols( A ) == 2 ) || ( rows( A ) == 3 && cols( A ) == 3 ) );
            if ( rows( A ) == 2 )
                return detail::computeCofactorImpl< row, col, 2 >( A, A );
            /*if( rows(A) == 3 )*/
            return detail::computeCofactorImpl< row, col, 3 >( A, A );
        }

        /**
         * @brief Compute the first directional derivative in direction \f$ B \f$ of the
         * \f$(row,col)\f$-cofactor of \f$ A \f$. Implemented for \f$ A\in \mathbb{R}^{n,n} \f$ with
         * \f$ n=2,3 \f$.
         *
         * The \f$(i,j)\f$-cofactor of a matrix \f$ A \f$ is \f$ (-1)^{i+j} \det(A^\#_{ij}) \f$,
         * where \f$ A^\#_{ij} \f$ is obtained from \f$ A \f$ by deleting the \f$i\f$-th row and \f$
         * j \f$-th column. If \f$ A\in \mathbb{R}^{3,3} \f$, then the cofactors are quadratic
         * polynomials of the entries of \f$ A^\#_{ij} \f$. In this case this function can also used
         * to compute the second directional derivative in directions \f$ A \f$ and \f$ B \f$.
         */
        template < int row, int col, ConstantSize Mat >
        auto computeCofactorDirectionalDerivative( const Mat& A,
                                                   const Mat& B ) requires( dim< Mat >() == 2 ||
                                                                            dim< Mat >() == 3 )
        {
            return detail::computeCofactorImpl< row, col, dim< Mat >() >( A, B );
        }

        /**
         * @brief Compute the first directional derivative in direction \f$ B \f$ of the
         * \f$(row,col)\f$-cofactor of \f$ A \f$. Implemented for \f$ A\in \mathbb{R}^{n,n} \f$ with
         * \f$ n=2,3 \f$.
         *
         * The \f$(i,j)\f$-cofactor of a matrix \f$ A \f$ is \f$ (-1)^{i+j} \det(A^\#_{ij}) \f$,
         * where \f$ A^\#_{ij} \f$ is obtained from \f$ A \f$ by deleting the \f$i\f$-th row and \f$
         * j \f$-th column. If \f$ A\in \mathbb{R}^{3,3} \f$, then the cofactors are quadratic
         * polynomials of the entries of \f$ A^\#_{ij} \f$. In this case this function can also used
         * to compute the second directional derivative in directions \f$ A \f$ and \f$ B \f$.
         */
        template < int row, int col, class Mat >
        auto computeCofactorDirectionalDerivative( const Mat& A, const Mat& B )
        {
            if ( rows( A ) == 2 )
                return detail::computeCofactorImpl< row, col, 2 >( A, B );
            /*if ( rows(A)==3 )*/
            return detail::computeCofactorImpl< row, col, 3 >( A, B );
        }

        /** @} */
    } // namespace linalg
} // namespace funcy
