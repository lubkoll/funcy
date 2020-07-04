#pragma once

#include <funcy/concepts.h>
#include <funcy/linalg/concepts.h>

#include <type_traits>

namespace funcy
{
    namespace linalg
    {

        namespace detail
        {

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
            template < template < class, int, int, int, int, int > class Matrix, class Scalar,
                       int n, int m, int option, int maxRows, int maxCols >
            struct GetTransposed< Matrix< Scalar, n, m, option, maxRows, maxCols > >
            {
                using type = Matrix< Scalar, m, n, option, maxCols, maxRows >;
            };

            /// For DUNE.
            template < template < class, unsigned, unsigned > class Matrix, class Scalar,
                       unsigned n, unsigned m >
            struct GetTransposed< Matrix< Scalar, n, m > >
            {
                using type = Matrix< Scalar, m, n >;
            };

            /// For deal.II.
            template < template < unsigned, unsigned, class > class Matrix, class Scalar,
                       unsigned n, unsigned m >
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
            /** @addtogroup ConceptCheck
             *  @{ */
            /// Check if object of type Matrix has a member function rows().
            template < class Mat >
            constexpr bool hasmem_fn_rows()
            {
                return false;
            }

            /// Check if object of type Matrix has a member function rows().
            template < class Mat >
            constexpr bool hasmem_fn_rows() requires requires( Mat m )
            {
                { m.rows() };
            }
            {
                return true;
            }

            /// Check if object of type Matrix has a member n_rows.
            template < class Mat >
            constexpr bool hasMem_n_rows()
            {
                return false;
            }

            /// Check if object of type Matrix has a member n_rows.
            template < class Mat >
            constexpr bool hasMem_n_rows() requires requires( Mat m )
            {
                { m.n_rows };
            }
            {
                return true;
            }

            /// Check if object of type Matrix has a member function cols().
            template < class Mat >
            constexpr bool hasmem_fn_cols()
            {
                return false;
            }

            /// Check if object of type Matrix has a member function cols().
            template < class Mat >
            constexpr bool hasmem_fn_cols() requires requires( Mat m )
            {
                { m.cols() };
            }
            {
                return true;
            }

            /// Check if object of type Matrix has a member n_cols.
            template < class Mat >
            constexpr bool hasMem_n_cols()
            {
                return false;
            }

            /// Check if object of type Matrix has a member n_cols.
            template < class Mat >
            constexpr bool hasMem_n_cols() requires requires( Mat m )
            {
                { m.n_cols };
            }
            {
                return true;
            }

            /// Check if object of type Vector has a member function size().
            template < class Vec >
            constexpr bool hasmem_fn_size()
            {
                return false;
            }

            /// Check if object of type Vector has a member function size().
            template < class Vec >
            constexpr bool hasmem_fn_size() requires requires( Vec v )
            {
                { v.size() };
            }
            {
                return true;
            }
            /** @} */
        } // namespace static_check

        /**
         * @brief Requires that a specialization of struct Zero exists for Matrix.
         * @return constant size zero matrix
         */
        template < Matrix Mat >
        constexpr Mat zero()
        {
            return Mat( 0 );
        }

        /**
         * @brief Requires that a specialization of struct Zero exists for Matrix.
         * @return constant size zero matrix
         */
        template < Matrix Mat >
        constexpr Mat zero() requires( std::is_default_constructible_v< Mat >&& requires( Mat m ) {
            m.fill( 0 );
        } )
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
        Mat zero( int rows, int cols ) requires(
            std::is_constructible_v< Mat, int, int >&& requires( Mat m ) { m.fill( 0 ); } )
        {
            Mat m( rows, cols );
            m.fill( 0 );
            return m;
        }

        template < Arithmetic Vec >
        constexpr Vec zero()
        {
            return Vec( 0 );
        }
    } // namespace linalg
} // namespace funcy
