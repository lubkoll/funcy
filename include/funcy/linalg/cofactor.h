#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/dimension.h>
#include <funcy/util/at.h>
#include <funcy/util/macros.h>

namespace funcy
{
    namespace linalg
    {
        /** @addtogroup LinearAlgebraGroup
         *  @{ */

        /// @cond
        namespace detail
        {
            constexpr int get_first( int row )
            {
                return ( row == 0 ) ? 1 : 0;
            }

            constexpr int get_last( int row )
            {
                return ( row == 2 ) ? 1 : 2;
            }

            template < int row, int col >
            struct CofactorIndices
            {
                static constexpr int first_row = get_first( row );
                static constexpr int last_row = get_last( row );
                static constexpr int first_col = get_first( col );
                static constexpr int last_col = get_last( col );
            };

            constexpr int sign( int row, int col )
            {
                return ( ( ( row + col ) % 2 == 0 ) ? 1 : -1 );
            }

            template < int row, int col, int dim, class Mat >
            auto compute_cofactor( const Mat&, const Mat& A ) requires( dim == 2 )
            {
                using Id = CofactorIndices< row, col >;
                return sign( row, col ) * at( A, Id::first_row, Id::first_col );
            }

            template < int row, int col, int dim, class Mat >
            auto compute_cofactor( const Mat& A, const Mat& B ) requires( dim == 3 )
            {
                using Id = CofactorIndices< row, col >;
                return sign( row, col ) * ( at( A, Id::first_row, Id::first_col ) *
                                                at( B, Id::last_row, Id::last_col ) -
                                            at( A, Id::first_row, Id::last_col ) *
                                                at( B, Id::last_row, Id::first_col ) );
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
        template < int row, int col, ConstantSize Mat >
        auto compute_cofactor( const Mat& A ) requires( dim< Mat >() == 2 || dim< Mat >() == 3 )
        {
            return detail::compute_cofactor< row, col, dim< Mat >() >( A, A );
        }

        /**
         * @brief Compute the \f$(row,col)\f$-cofactor of \f$ A \f$. Implemented for \f$ A\in
         * \mathbb{R}^{n,n} \f$ with \f$ n=2,3 \f$.
         *
         * The \f$(i,j)\f$-cofactor of a matrix \f$ A \f$ is \f$ (-1)^{i+j} \det(A^\#_{ij}) \f$,
         * where \f$ A^\#_ij \f$ is obtained from \f$ A \f$ by deleting the \f$i\f$-th row and \f$ j
         * \f$-th column.
         */
        template < int row, int col, class Mat >
        auto compute_cofactor( const Mat& A )
        {
            FUNCY_ASSERT( ( rows( A ) == 2 && cols( A ) == 2 ) ||
                          ( rows( A ) == 3 && cols( A ) == 3 ) );
            if ( rows( A ) == 2 )
                return detail::compute_cofactor< row, col, 2 >( A, A );
            /*if( rows(A) == 3 )*/
            return detail::compute_cofactor< row, col, 3 >( A, A );
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
        auto compute_cofactor_directional_derivative( const Mat& A,
                                                      const Mat& B ) requires( dim< Mat >() == 2 ||
                                                                               dim< Mat >() == 3 )
        {
            return detail::compute_cofactor< row, col, dim< Mat >() >( A, B );
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
        auto compute_cofactor_directional_derivative( const Mat& A, const Mat& B )
        {
            if ( rows( A ) == 2 )
                return detail::compute_cofactor< row, col, 2 >( A, B );
            /*if ( rows(A)==3 )*/
            return detail::compute_cofactor< row, col, 3 >( A, B );
        }

        /** @} */
    } // namespace linalg
} // namespace funcy
