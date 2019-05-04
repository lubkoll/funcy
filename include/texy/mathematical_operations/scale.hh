#pragma once

#include <type_traits>
#include <utility>

#include <texy/util/chainer.hh>
#include <funcy/concept_check.hh>
#include <funcy/util/derivative_wrappers.hh>
#include <funcy/util/evaluate_if_present.hh>
#include <funcy/util/indexed_type.hh>
#include <funcy/util/mathop_traits.hh>

namespace texy
{
    namespace mathop
    {
        /**
         * @ingroup TexifyMathematicalOperationsGroup
         * @brief Scaling \f$ af \f$ of some function \f$ f \f$ with a double \f$ a \f$ (F must
         * satisfy the requirements of concepts::FunctionConcept).
         */
        template < class Scalar, class F, class = funcy::concepts::FunctionConceptCheck< F > >
        struct Scale : Chainer< Scale< Scalar, F, funcy::concepts::FunctionConceptCheck< F > > >
        {
            /**
             * @brief Constructor passing arguments to function constructor.
             * @param a_ scaling
             * @param f_ input for constructor of outer function
             */
            template < class... InitF >
            constexpr Scale( Scalar a_, InitF&&... f_ )
                : a( a_ ), f( std::forward< InitF >( f_ )... ),
                  value( funcy::multiply_via_traits( a, f() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present( f, x );
                value = funcy::multiply_via_traits( a, f() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present< index >( f, x );
                value = funcy::multiply_via_traits( a, f() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            template < int idx, class Arg, class IndexedArg = funcy::IndexedType< Arg, idx >,
                       class = std::enable_if_t< funcy::D1< F, IndexedArg >::present > >
            auto d1( const Arg& dx ) const
            {
                return funcy::multiply_via_traits( a, funcy::D1_< F, IndexedArg >::apply( f, dx ) );
            }

            /// Second directional derivative.
            template <
                int idx, int idy, class ArgX, class ArgY,
                class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                class = std::enable_if_t< funcy::D2< F, IndexedArgX, IndexedArgY >::present > >
            auto d2( const ArgX& dx, const ArgY& dy ) const
            {
                return funcy::multiply_via_traits(
                    a, funcy::D2_< F, IndexedArgX, IndexedArgY >::apply( f, dx, dy ) );
            }

            /// Third directional derivative.
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                       class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                       class IndexedArgZ = funcy::IndexedType< ArgZ, idz >,
                       class = std::enable_if_t<
                           funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::present > >
            auto d3( const ArgX& dx, const ArgY& dy, const ArgZ& dz ) const
            {
                return funcy::multiply_via_traits(
                    a,
                    funcy::D3_< F, IndexedArgX, IndexedArgY, IndexedArgZ >::apply( f, dx, dy, dz ) );
            }

        private:
            Scalar a = 1.;
            F f;
            std::decay_t< decltype( std::declval< F >()() ) > value;
        };
    }
}
