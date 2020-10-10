#pragma once

#include <funcy/linalg/concepts.h>
#include <funcy/util/macros.h>

namespace funcy
{
    namespace linalg
    {

// suppress warnings coming from the __attribute__((always_inline))
#if defined( __GNUC__ ) || defined( __GNUG__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

        /// Access matrix entry \f$A_{ij}\f via square brackets$.
        template < Matrix M, class Index >
        FUNCY_ALWAYS_INLINE decltype( auto ) at( M&& A, Index i,
                                                 Index j ) requires requires( std::decay_t< M > A )
        {
            { A[ 0 ][ 0 ] };
        }
        {
            return A[ i ][ j ];
        }

        /// Access matrix entry \f$A_{ij}\f via square brackets$.
        template < Matrix M, class Index >
        FUNCY_ALWAYS_INLINE decltype( auto ) at( M&& A, Index i,
                                                 Index j ) requires requires( std::decay_t< M > A )
        {
            { A( 0, 0 ) };
        }
        {
            return A( i, j );
        }

        /// Access vector entry \f$\v_if$.
        template < Vector V, class Index >
        FUNCY_ALWAYS_INLINE decltype( auto )
        at( V&& v, Index i ) requires( !Matrix< std::decay_t< V > > &&
                                       requires( std::decay_t< V > v ) { { v[ 0 ] }; } )
        {
            return v[ i ];
        }

        /// Access vector entry \f$\v_if$.
        template < Vector V, class Index >
        FUNCY_ALWAYS_INLINE decltype( auto )
        at( V&& v, Index i ) requires( !Matrix< std::decay_t< V > > &&
                                       requires( std::decay_t< V > v ) { { v( 0 ) }; } )
        {
            return v( i );
        }
#if defined( __GNUC__ ) || defined( __GNUG__ )
#pragma GCC diagnostic pop
#endif
    } // namespace linalg
} // namespace funcy
