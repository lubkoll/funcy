#pragma once

#include <type_traits>

namespace funcy
{
    namespace linalg
    {
        /// Specialize this for your matrix class. Number of rows must be provided by a static
        /// member variable called value.
        template < class Matrix >
        struct NumberOfRows : std::integral_constant< int, -1 >
        {
        };

        /// Specialize this for your matrix class. Number of columns must be provided by a static
        /// member variable called value.
        template < class Matrix >
        struct NumberOfColumns : std::integral_constant< int, -1 >
        {
        };

        /// @cond
        /// Specialization for matrices.
        template < template < class, int, int... > class Matrix, class T, int n, int... m >
        struct NumberOfRows< Matrix< T, n, m... > > : std::integral_constant< int, n >
        {
        };

        /// Specialization for matrices.
        template < template < class, unsigned, unsigned > class Matrix, class T, unsigned n,
                   unsigned m >
        struct NumberOfRows< Matrix< T, n, m > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for matrices.
        template < template < int, int, class > class Matrix, class T, int n, int m >
        struct NumberOfRows< Matrix< n, m, T > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for matrices.
        template < template < unsigned, unsigned, class > class Matrix, class T, unsigned n,
                   unsigned m >
        struct NumberOfRows< Matrix< n, m, T > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for matrices.
        template < template < int, int > class Matrix, int n, int m >
        struct NumberOfRows< Matrix< n, m > > : std::integral_constant< int, n >
        {
        };

        /// Specialization for matrices.
        template < template < unsigned, unsigned > class Matrix, unsigned n, unsigned m >
        struct NumberOfRows< Matrix< n, m > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for vectors.
        template < template < class, int > class Vector, class T, int n >
        struct NumberOfRows< Vector< T, n > > : std::integral_constant< int, n >
        {
        };

        /// Specialization for vectors.
        template < template < class, unsigned > class Vector, class T, unsigned n >
        struct NumberOfRows< Vector< T, n > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for vectors.
        template < template < int > class Vector, int n >
        struct NumberOfRows< Vector< n > > : std::integral_constant< int, n >
        {
        };

        /// Specialization for vectors.
        template < template < unsigned > class Vector, unsigned n >
        struct NumberOfRows< Vector< n > > : std::integral_constant< unsigned, n >
        {
        };

        /// Specialization for matrices.
        template < template < class, int, int, int... > class Matrix, class T, int n, int m,
                   int... other >
        struct NumberOfColumns< Matrix< T, n, m, other... > > : std::integral_constant< int, m >
        {
        };

        /// Specialization for matrices.
        template < template < class, int, int > class Matrix, class T, int n, int m >
        struct NumberOfColumns< Matrix< T, n, m > > : std::integral_constant< int, m >
        {
        };

        /// Specialization for matrices.
        template < template < class, unsigned, unsigned > class Matrix, class T, unsigned n,
                   unsigned m >
        struct NumberOfColumns< Matrix< T, n, m > > : std::integral_constant< unsigned, m >
        {
        };

        /// Specialization for matrices.
        template < template < int, int, class > class Matrix, class T, int n, int m >
        struct NumberOfColumns< Matrix< n, m, T > > : std::integral_constant< int, m >
        {
        };

        /// Specialization for matrices.
        template < template < unsigned, unsigned, class > class Matrix, class T, unsigned n,
                   unsigned m >
        struct NumberOfColumns< Matrix< n, m, T > > : std::integral_constant< unsigned, m >
        {
        };

        /// Specialization for matrices.
        template < template < int, int > class Matrix, int n, int m >
        struct NumberOfColumns< Matrix< n, m > > : std::integral_constant< int, m >
        {
        };

        /// Specialization for matrices.
        template < template < unsigned, unsigned > class Matrix, unsigned n, unsigned m >
        struct NumberOfColumns< Matrix< n, m > > : std::integral_constant< unsigned, m >
        {
        };

        template < class >
        struct GetTransposed;

        template < template < int, int > class Matrix, int n, int m >
        struct GetTransposed< Matrix< n, m > >
        {
            using type = Matrix< m, n >;
        };

        template < template < unsigned, unsigned > class Matrix, unsigned n, unsigned m >
        struct GetTransposed< Matrix< n, m > >
        {
            using type = Matrix< m, n >;
        };

        template < template < class, int, int > class Matrix, class Scalar, int n, int m >
        struct GetTransposed< Matrix< Scalar, n, m > >
        {
            using type = Matrix< Scalar, m, n >;
        };

        /// For Eigen.
        template < template < class, int, int, int, int, int > class Matrix, class Scalar, int n,
                   int m, int option, int maxRows, int maxCols >
        struct GetTransposed< Matrix< Scalar, n, m, option, maxRows, maxCols > >
        {
            using type = Matrix< Scalar, m, n, option, maxCols, maxRows >;
        };

        /// For DUNE.
        template < template < class, unsigned, unsigned > class Matrix, class Scalar, unsigned n,
                   unsigned m >
        struct GetTransposed< Matrix< Scalar, n, m > >
        {
            using type = Matrix< Scalar, m, n >;
        };

        /// For deal.II.
        template < template < unsigned, unsigned, class > class Matrix, class Scalar, unsigned n,
                   unsigned m >
        struct GetTransposed< Matrix< n, m, Scalar > >
        {
            using type = Matrix< m, n, Scalar >;
        };

        template < class Matrix >
        using Transposed_t = typename GetTransposed< Matrix >::type;
        /// @endcond
    } // namespace linalg
} // namespace funcy
