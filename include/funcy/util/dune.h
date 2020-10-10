#pragma once

#ifdef FUNCY_FOUND_DUNE

#include <funcy/util/mathop_traits.h>

#include <dune/common/fmatrix.hh>

namespace funcy
{
    template < class Scalar, int n, int m >
    struct MathOpTraits< Dune::FieldMatrix< Scalar, n, m >, void >
    {
        static constexpr auto multiply( const Dune::FieldMatrix< Scalar, n, m >& lhs,
                                        const Dune::FieldMatrix< Scalar, n, m >& rhs )
        {
            return lhs.rightmultiplyany( rhs );
        }

        static constexpr auto add( const Dune::FieldMatrix< Scalar, n, m >& lhs,
                                   const Dune::FieldMatrix< Scalar, n, m >& rhs )
        {
            return lhs + rhs;
        }

        static constexpr auto subtract( const Dune::FieldMatrix< Scalar, n, m >& lhs,
                                        const Dune::FieldMatrix< Scalar, n, m >& rhs )
        {
            return lhs - rhs;
        }
    };
} // namespace funcy

#endif
