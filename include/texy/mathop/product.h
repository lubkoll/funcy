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

namespace texy
{
    namespace mathop
    {
        /**
         * @ingroup TexifyMathematicalOperationsGroup
         * @brief %Product \f$fg\f$ of functions of type F and G (F and G must satisfy the
         * requirements of Concepts::FunctionConcept).
         */
        template < class F, class G, class = funcy::Concepts::IsFunction< F >,
                   class = funcy::Concepts::IsFunction< G > >
        struct Product : Chainer< Product< F, G, funcy::Concepts::IsFunction< F >,
                                           funcy::Concepts::IsFunction< G > > >
        {
        private:
            template < class IndexedArg >
            using D1Type = funcy::ComputeSum<
                funcy::ComputeProduct< funcy::D1< F, IndexedArg >, funcy::D0< G > >,
                funcy::ComputeProduct< funcy::D0< F >, funcy::D1< G, IndexedArg > > >;

            template < class IndexedArgX, class IndexedArgY >
            using D2Type = funcy::ComputeSum<
                funcy::ComputeProduct< funcy::D2< F, IndexedArgX, IndexedArgY >, funcy::D0< G > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgX >, funcy::D1< G, IndexedArgY > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgY >, funcy::D1< G, IndexedArgX > >,
                funcy::ComputeProduct< funcy::D0< F >, funcy::D2< G, IndexedArgX, IndexedArgY > > >;

            template < class IndexedArgX, class IndexedArgY, class IndexedArgZ >
            using D3Type = funcy::ComputeSum<
                funcy::ComputeProduct< funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                      funcy::D0< G > >,
                funcy::ComputeProduct< funcy::D2< F, IndexedArgX, IndexedArgY >,
                                      funcy::D1< G, IndexedArgZ > >,
                funcy::ComputeProduct< funcy::D2< F, IndexedArgX, IndexedArgZ >,
                                      funcy::D1< G, IndexedArgY > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgX >,
                                      funcy::D2< G, IndexedArgY, IndexedArgZ > >,
                funcy::ComputeProduct< funcy::D2< F, IndexedArgY, IndexedArgZ >,
                                      funcy::D1< G, IndexedArgX > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgY >,
                                      funcy::D2< G, IndexedArgX, IndexedArgZ > >,
                funcy::ComputeProduct< funcy::D1< F, IndexedArgZ >,
                                      funcy::D2< G, IndexedArgX, IndexedArgY > >,
                funcy::ComputeProduct< funcy::D0< F >,
                                      funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > > >;

        public:
            /**
             * @brief Constructor passing arguments to function constructors.
             * @param f_ input for constructor of left side of product
             * @param g_ input for constructor of right side of product
             */
            template < class InitF, class InitG >
            constexpr Product( InitF&& f_, InitG&& g_ )
                : f( std::forward< InitF >( f_ ) ), g( std::forward< InitG >( g_ ) ),
                  value( funcy::multiply_via_traits( f(), g() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( Arg const& x )
            {
                funcy::update_if_present( f, x );
                funcy::update_if_present( g, x );
                value = funcy::multiply_via_traits( f(), g() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present< index >( f, x );
                funcy::update_if_present< index >( g, x );
                value = funcy::multiply_via_traits( f(), g() );
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
                       class = std::enable_if_t< D1Type< IndexedArg >::present > >
            auto d1( Arg const& dx ) const
            {
                return sum(
                    funcy::product( funcy::D1< F, IndexedArg >( f, dx ), funcy::D0< G >( g ) ),
                    funcy::product( funcy::D0< F >( f ), funcy::D1< G, IndexedArg >( g, dx ) ) )();
            }

            /**
             * @brief Second directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             */
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                       class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                       class = std::enable_if_t< D2Type< IndexedArgX, IndexedArgY >::present > >
            auto d2( ArgX const& dx, ArgY const& dy ) const
            {
                return funcy::sum(
                    funcy::product( funcy::D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ),
                                   funcy::D0< G >( g ) ),
                    funcy::product( funcy::D1< F, IndexedArgX >( f, dx ),
                                   funcy::D1< G, IndexedArgY >( g, dy ) ),
                    funcy::product( funcy::D1< F, IndexedArgY >( f, dy ),
                                   funcy::D1< G, IndexedArgX >( g, dx ) ),
                    funcy::product( funcy::D0< F >( f ),
                                   funcy::D2< G, IndexedArgX, IndexedArgY >( g, dx, dy ) ) )();
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
                           D3Type< IndexedArgX, IndexedArgY, IndexedArgZ >::present > >
            auto d3( ArgX const& dx, ArgY const& dy, ArgZ const& dz ) const
            {
                return funcy::sum(
                    funcy::product(
                        funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >( f, dx, dy, dz ),
                        funcy::D0< G >( g ) ),
                    funcy::product( funcy::D2< F, IndexedArgX, IndexedArgY >( f, dx, dy ),
                                   funcy::D1< G, IndexedArgZ >( g, dz ) ),
                    funcy::product( funcy::D2< F, IndexedArgX, IndexedArgZ >( f, dx, dz ),
                                   funcy::D1< G, IndexedArgY >( g, dy ) ),
                    funcy::product( funcy::D1< F, IndexedArgX >( f, dx ),
                                   funcy::D2< G, IndexedArgY, IndexedArgZ >( g, dy, dz ) ),
                    funcy::product( funcy::D2< F, IndexedArgY, IndexedArgZ >( f, dy, dz ),
                                   funcy::D1< G, IndexedArgX >( g, dx ) ),
                    funcy::product( funcy::D1< F, IndexedArgY >( f, dy ),
                                   funcy::D2< G, IndexedArgX, IndexedArgZ >( g, dx, dz ) ),
                    funcy::product( funcy::D1< F, IndexedArgZ >( f, dz ),
                                   funcy::D2< G, IndexedArgX, IndexedArgY >( g, dx, dy ) ),
                    funcy::product(
                        funcy::D0< F >( f ),
                        funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ >( g, dx, dy, dz ) ) )();
            }

        private:
            F f;
            G g;
            funcy::decay_t< decltype(
                funcy::multiply_via_traits( std::declval< F >()(), std::declval< G >()() ) ) >
                value;
        };
    }
}
