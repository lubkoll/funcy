#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/at.h>
#include <funcy/linalg/concepts.h>
#include <funcy/linalg/rows_and_cols.h>
#include <funcy/linalg/type_traits.h>
#include <funcy/util/chainer.h>
#include <funcy/util/macros.h>

#include <concepts>
#include <type_traits>

namespace funcy::linalg
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
        [[nodiscard]] Transposed_t< Mat >
        transpose( Mat A ) requires std::same_as< Mat, Transposed_t< Mat > >
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
        [[nodiscard]] Transposed_t< Mat >
        transpose( const Mat& A ) requires( !std::same_as< Mat, Transposed_t< Mat > > )
        {
            auto B = zero< Transposed_t< Mat > >();
            for ( int i = 0; i < rows< Mat >(); ++i )
                for ( int j = 0; j < cols< Mat >(); ++j )
                    at( B, j, i ) = A( i, j );
            return B;
        }

        /// Compute transpose of square matrix.
        template < class Mat >
        [[nodiscard]] Mat transpose( Mat A ) requires( !ConstantSize< Mat > )
        {
            FUNCY_ASSERT( rows( A ) == cols( A ) );
            using Index = decltype( rows( std::declval< Mat >() ) );
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

        /**
         * @brief Overwrites \f$A\f$ with \f$A+A^T\f$.
         * @return \f$A+A^T\f$
         */
        template < ConstantSize Mat >
        [[nodiscard]] Mat& add_transposed( Mat& A )
        {
            using linalg::dim;
            using Index = decltype( dim< Mat >() );
            for ( Index i = 0; i < dim< Mat >(); ++i )
                for ( Index j = i + 1; j < dim< Mat >(); ++j )
                    at( A, j, i ) = at( A, i, j ) = at( A, i, j ) + at( A, j, i );
            for ( Index i = 0; i < dim< Mat >(); ++i )
                at( A, i, i ) *= 2;
            return A;
        }

        /**
         * @brief Overwrites \f$A\f$ with \f$A+A^T\f$.
         * @return \f$A+A^T\f$
         */
        template < class Mat >
        [[nodiscard]] Mat& add_transposed( Mat& A )
        {
            using linalg::cols;
            using linalg::rows;
            FUNCY_ASSERT( rows( A ) == cols( A ) );
            using Index = decltype( rows( std::declval< Mat >() ) );
            for ( Index i = 0; i < rows( A ); ++i )
                for ( Index j = i + 1; j < cols( A ); ++j )
                    at( A, j, i ) = at( A, i, j ) = at( A, i, j ) + at( A, j, i );
            for ( Index i = 0; i < rows( A ); ++i )
                at( A, i, i ) *= 2;
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

        [[nodiscard]] const auto& d0() const noexcept
        {
            return AT_;
        }

        [[nodiscard]] auto d1( const Mat& dA ) const
        {
            return detail::transpose( dA );
        }

    private:
        typename detail::WrappedMatrix< Mat >::type AT_;
    };

    /**
     * @brief Generate \f$A^T\in\mathbb{R}^{n,n}\f$.
     * @param A square matrix
     * @return Transpose<Matrix>(A)
     */
    template < class Mat >
    [[nodiscard]] auto transpose( const Mat& A )
    {
        return Transpose( A );
    }

    /**
     * @brief Generate \f$f^T\f$, where \f$f:\cdot\mapsto\mathbb{R}^{n,n} \f$.
     * @param f function object mapping into a space of square matrices
     * @return Transpose< decay_t<decltype(f())> >(f())( f )
     */
    template < Function F >
    [[nodiscard]] auto transpose( const F& f )
    {
        return Transpose< decay_t< decltype( f() ) > >( f() )( f );
    }
    /** @} */
} // namespace funcy::linalg
