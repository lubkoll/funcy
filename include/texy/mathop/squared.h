#pragma once

#include <type_traits>
#include <utility>

#include <texy/util/chainer.h>
#include <funcy/concept_check.h>
#include <funcy/util/compute_product.h>
#include <funcy/util/compute_sum.h>
#include <funcy/util/derivative_wrappers.h>
#include <funcy/util/evaluate_if_present.h>
#include <funcy/util/indexed_type.h>
#include <funcy/util/mathop_traits.h>
#include <funcy/util/type_traits.h>

namespace texy
{
    namespace mathop
    {
        /**
         * @ingroup TexifyMathematicalOperationsGroup
         * @brief %Squared function \f$f^2\f$.
         */
        template < class F, class = funcy::Concepts::IsFunction< F > >
        struct Squared : Chainer< Squared< F, funcy::Concepts::IsFunction< F > > >
        {
        private:
            template < class IndexedArgX, class IndexedArgY >
            using D2Sum = funcy::ComputeSum<
                funcy::ComputeProduct< funcy::D0< F >, funcy::D2< F, IndexedArgX, IndexedArgY > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgY >, funcy::D1< F, IndexedArgX > > >;

            template < class IndexedArgX, class IndexedArgY, class IndexedArgZ >
            using D3Sum = funcy::ComputeSum<
                funcy::ComputeProduct< funcy::D0< F >,
                                      funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgZ >,
                                      funcy::D2< F, IndexedArgX, IndexedArgY > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgY >,
                                      funcy::D2< F, IndexedArgX, IndexedArgZ > >,
                funcy::ComputeProduct< funcy::D2< F, IndexedArgY, IndexedArgZ >,
                                      funcy::D1< F, IndexedArgX > > >;

        public:
            /**
             * @brief Constructor
             * @param f_ initializer for F
             */
            template < class InitF,
                       std::enable_if_t< !std::is_same< std::decay_t< InitF >, Squared >::value >* =
                           nullptr >
            constexpr Squared( InitF&& f_ )
                : f( std::forward< InitF >( f_ ) ), value( funcy::multiply_via_traits( f(), f() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( Arg const& x )
            {
                funcy::update_if_present( f, x );
                value = funcy::multiply_via_traits( f(), f() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present< index >( f, x );
                value = funcy::multiply_via_traits( f(), f() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /**
             * @brief First directional derivative.
             * @param dx direction for which the derivative is computed
             */
            template < int id, class Arg, class IndexedArg = funcy::IndexedType< Arg, id >,
                       class = std::enable_if_t< funcy::ComputeProduct<
                           funcy::D0< F >, funcy::D1< F, IndexedArg > >::present > >
            auto d1( Arg const& dx ) const
                -> funcy::decay_t< decltype( funcy::multiply_via_traits( std::declval< F >()(),
                                                                       std::declval< F >()() ) ) >
            {
                return funcy::multiply_via_traits(
                    2,
                    funcy::multiply_via_traits( f(), funcy::D1_< F, IndexedArg >::apply( f, dx ) ) );
            }

            /**
             * @brief Second directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             */
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                       class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                       class = std::enable_if_t< D2Sum< IndexedArgX, IndexedArgY >::present > >
            auto d2( ArgX const& dx, ArgY const& dy ) const
                -> funcy::decay_t< decltype( funcy::multiply_via_traits( std::declval< F >()(),
                                                                       std::declval< F >()() ) ) >
            {
                return multiply_via_traits(
                    2, sum( product( funcy::D0< F >( f ),
                                     funcy::D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ) ),
                            product( funcy::D1< F, IndexedArgY >( f, dy ),
                                     funcy::D1< F, IndexedArgX >( f, dx ) ) )() );
            }

            /**
             * @brief Third directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             * @param dz direction for which the derivative is computed
             */
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                       class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                       class IndexedArgZ = funcy::IndexedType< ArgZ, idz >,
                       class = std::enable_if_t<
                           D3Sum< IndexedArgX, IndexedArgY, IndexedArgZ >::present > >
            auto d3( ArgX const& dx, ArgY const& dy, ArgZ const& dz ) const
                -> funcy::decay_t< decltype( funcy::multiply_via_traits( std::declval< F >()(),
                                                                       std::declval< F >()() ) ) >
            {
                return multiply_via_traits(
                    2, sum( product( funcy::D0< F >( f ),
                                     funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >(
                                         f, dx, dy, dz ) ),
                            product( funcy::D1< F, IndexedArgZ >( f, dz ),
                                     funcy::D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ) ),
                            product( funcy::D1< F, IndexedArgY >( f, dy ),
                                     funcy::D2< F, IndexedArgX, IndexedArgZ >( f, dx, dz ) ),
                            product( funcy::D2< F, IndexedArgY, IndexedArgZ >( f, dy, dz ),
                                     funcy::D1< F, IndexedArgX >( f, dx ) ) )() );
            }

        private:
            F f;
            funcy::decay_t< decltype(
                funcy::multiply_via_traits( std::declval< F >()(), std::declval< F >()() ) ) >
                value;
        };
    }
}
