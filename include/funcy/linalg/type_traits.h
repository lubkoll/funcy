#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>

#include <type_traits>

namespace funcy::linalg
{
    namespace detail
    {
        /// @cond
        template < template < class, auto, auto > class Matrix, class T, auto n, auto m >
        struct NumberOfRows< Matrix< T, n, m > > : std::integral_constant< int, n >
        {
        };

        template < template < class, auto, auto, auto, auto, auto > class Matrix, class T, auto n,
                   auto m, auto o, auto p, auto q >
        struct NumberOfRows< Matrix< T, n, m, o, p, q > > : std::integral_constant< int, n >
        {
        };

        template < template < auto, auto, class > class Matrix, class T, auto n, auto m >
        struct NumberOfRows< Matrix< n, m, T > > : std::integral_constant< int, n >
        {
        };

        template < template < auto, auto > class Matrix, auto n, auto m >
        struct NumberOfRows< Matrix< n, m > > : std::integral_constant< int, n >
        {
        };

        template < template < class, auto > class Vector, class T, auto n >
        struct NumberOfRows< Vector< T, n > > : std::integral_constant< int, n >
        {
        };

        template < template < auto > class Vector, auto n >
        struct NumberOfRows< Vector< n > > : std::integral_constant< int, n >
        {
        };

        template < template < class, auto, auto, auto, auto, auto > class Matrix, class T, auto n,
                   auto m, auto o, auto p, auto q >
        struct NumberOfColumns< Matrix< T, n, m, o, p, q > > : std::integral_constant< int, m >
        {
        };

        template < template < class, auto, auto > class Matrix, class T, auto n, auto m >
        struct NumberOfColumns< Matrix< T, n, m > > : std::integral_constant< int, m >
        {
        };

        template < template < auto, auto, class > class Matrix, class T, auto n, auto m >
        struct NumberOfColumns< Matrix< n, m, T > > : std::integral_constant< int, m >
        {
        };

        template < template < auto, auto > class Matrix, auto n, auto m >
        struct NumberOfColumns< Matrix< n, m > > : std::integral_constant< int, m >
        {
        };

        template < template < auto, auto > class Matrix, auto n, auto m >
        struct GetTransposed< Matrix< n, m > >
        {
            using type = Matrix< m, n >;
        };

        /// For DUNE.
        template < template < class, auto, auto > class Matrix, class Scalar, auto n, auto m >
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

        /// For deal.II.
        template < template < auto, auto, class > class Matrix, class Scalar, auto n, auto m >
        struct GetTransposed< Matrix< n, m, Scalar > >
        {
            using type = Matrix< m, n, Scalar >;
        };

        template < class Matrix >
        using Transposed_t = typename GetTransposed< Matrix >::type;
    } // namespace detail
      /// @endcond
      ///
    namespace static_check
    {
        /// Check if object of type Matrix has a member function rows().
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_fn_rows()
        {
            return false;
        }

        /// Check if object of type Matrix has a member function rows().
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_fn_rows() requires requires( Mat m )
        {
            { m.rows() };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member n_rows.
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_n_rows()
        {
            return false;
        }

        /// Check if object of type Matrix has a member n_rows.
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_n_rows() requires requires( Mat m )
        {
            { m.n_rows };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member function cols().
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_fn_cols()
        {
            return false;
        }

        /// Check if object of type Matrix has a member function cols().
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_fn_cols() requires requires( Mat m )
        {
            { m.cols() };
        }
        {
            return true;
        }

        /// Check if object of type Matrix has a member n_cols.
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_n_cols()
        {
            return false;
        }

        /// Check if object of type Matrix has a member n_cols.
        template < class Mat >
        [[nodiscard]] constexpr bool has_mem_n_cols() requires requires( Mat m )
        {
            { m.n_cols };
        }
        {
            return true;
        }

        /// Check if object of type Vector has a member function size().
        template < class Vec >
        [[nodiscard]] constexpr bool has_mem_fn_size()
        {
            return false;
        }

        /// Check if object of type Vector has a member function size().
        template < class Vec >
        [[nodiscard]] constexpr bool has_mem_fn_size() requires requires( Vec v )
        {
            { v.size() };
        }
        {
            return true;
        }
    } // namespace static_check

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < Matrix Mat >
    [[nodiscard]] constexpr Mat zero()
    {
        return Mat( 0 );
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return constant size zero matrix
     */
    template < Matrix Mat >
    [[nodiscard]] constexpr Mat
    zero() requires( std::is_default_constructible_v< Mat >&& requires( Mat m ) { m.fill( 0 ); } )
    {
        Mat m;
        m.fill( 0 );
        return m;
    }

    /**
     * @brief Requires that a specialization of struct Zero exists for Matrix.
     * @return dynamic size zero matrix
     */
    template < Matrix Mat >
    [[nodiscard]] Mat zero( int rows, int cols ) requires(
        std::is_constructible_v< Mat, int, int >&& requires( Mat m ) { m.fill( 0 ); } )
    {
        Mat m( rows, cols );
        m.fill( 0 );
        return m;
    }

    template < Arithmetic Vec >
    [[nodiscard]] constexpr Vec zero()
    {
        return Vec( 0 );
    }
} // namespace funcy::linalg
