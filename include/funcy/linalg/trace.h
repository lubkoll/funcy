#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/at.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/dimension.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/util/chainer.h>
#include <funcy/util/exceptions.h>

#include <type_traits>
#include <utility>

namespace funcy::linalg
{
    /** @addtogroup LinearAlgebraGroup
     *  @{ */

    /// @cond
    namespace detail
    {
        template < int dim, SquareMatrix Matrix >
        [[nodiscard]] auto compute_trace( const Matrix& A ) requires( dim != 2 && dim != 3 )
        {
            auto val = at( A, 0, 0 );
            for ( int i = 1; i < rows< Matrix >(); ++i )
                val += at( A, i, i );
            return val;
        }

        template < int dim, SquareMatrix Matrix >
        [[nodiscard]] auto compute_trace( const Matrix& A ) requires( dim == 2 )

        {
            return at( A, 0, 0 ) + at( A, 1, 1 );
        }

        template < int dim, SquareMatrix Matrix >
        [[nodiscard]] auto compute_trace( const Matrix& A ) requires( dim == 3 )
        {
            return at( A, 0, 0 ) + at( A, 1, 1 ) + at( A, 2, 2 );
        }
    } // namespace detail

    /// %Trace of a matrix, i.e. sum of diagonal elements.
    template < SquareMatrix Mat >
    struct ConstantSizeTrace : Chainer< ConstantSizeTrace< Mat > >
    {
        ConstantSizeTrace() = default;

        /**
         * @brief Constructor.
         * @param A point of evaluation.
         */
        explicit ConstantSizeTrace( const Mat& A )
        {
            update( A );
        }

        /// Reset point of evaluation.
        void update( const Mat& A )
        {
            trace = detail::compute_trace< dim< Mat >() >( A );
        }

        /// Function value.
        [[nodiscard]] auto d0() const noexcept
        {
            return trace;
        }

        /// First directional derivative.
        [[nodiscard]] auto d1( const Mat& dA ) const
        {
            return detail::compute_trace< dim< Mat >() >( dA );
        }

    private:
        decltype( detail::compute_trace< dim< Mat >() >( std::declval< Mat >() ) ) trace = 0;
    };

    /// %Trace of a matrix, i.e. sum of diagonal elements.
    template < class Mat >
    struct DynamicSizeTrace : Chainer< DynamicSizeTrace< Mat > >
    {
        DynamicSizeTrace() = default;

        /**
         * @brief Constructor.
         * @param A point of evaluation.
         */
        explicit DynamicSizeTrace( const Mat& A )
        {
            update( A );
        }

        /// Reset point of evaluation.
        void update( const Mat& A )
        {
#ifdef FUNCY_ENABLE_EXCEPTIONS
            if ( rows( A ) != cols( A ) )
                throw NonSymmetricMatrixException( "DynamicSizeTrace", rows( A ), cols( A ),
                                                   __FILE__, __LINE__ );
#endif
            using Index = decltype( rows( std::declval< Mat >() ) );
            trace = 0.;
            for ( Index i = 0; i < rows( A ); ++i )
                trace += at( A, i, i );
        }

        /// Function value.
        [[nodiscard]] auto d0() const noexcept
        {
            return trace;
        }

        /// First directional derivative.
        [[nodiscard]] auto d1( const Mat& dA ) const
        {
            using Index = decltype( rows( dA ) );
            auto result = decltype( at( dA, 0, 0 ) )( 0. );
            for ( Index i = 0; i < rows( dA ); ++i )
                result += at( dA, i, i );
            return result;
        }

    private:
        std::decay_t< decltype( at( std::declval< Mat >(), 0, 0 ) ) > trace = 0;
    };
    /// @endcond

    /**
     * @brief Generate \f$\mathrm{tr}(A)\in\mathbb{R}^{n,n}\f$.
     * @param A matrix
     * @return DynamicSizeTrace<Mat>(A)
     */
    template < class Mat >
    [[nodiscard]] auto trace( const Mat& A ) requires( !Function< Mat > && !ConstantSize< Mat > )
    {
        return DynamicSizeTrace( A );
    }

    /**
     * @brief Generate \f$\mathrm{tr}(A)\in\mathbb{R}^{n,n}\f$.
     * @param A matrix
     * @return ConstantSizeTrace<Mat>(A)
     */
    template < ConstantSize Mat >
    [[nodiscard]] auto trace( const Mat& A ) requires( !Function< Mat > )
    {
        return ConstantSizeTrace( A );
    }

    /**
     * @brief Generate \f$\mathrm{tr}\circ f\f$, where \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$.
     * @param f function object mapping into a space of square matrices
     */
    template < Function F >
    [[nodiscard]] auto trace( const F& f )
    {
        return trace( f() )( f );
    }
    /** @} */
} // namespace funcy::linalg
