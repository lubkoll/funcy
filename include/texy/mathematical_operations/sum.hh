#pragma once

#include <texy/util/chainer.hh>
#include <funcy/concept_check.hh>
#include <funcy/util/compute_sum.hh>
#include <funcy/util/derivative_wrappers.hh>
#include <funcy/util/evaluate_if_present.hh>
#include <funcy/util/indexed_type.hh>
#include <funcy/util/mathop_traits.hh>

#include <type_traits>
#include <utility>

namespace texy
{
    namespace MathematicalOperations
    {
        /**
         * \ingroup TexifyMathematicalOperationsGroup
         * \brief %Sum of functions of type F and G (F and G must satisfy the requirements of
         * Concepts::FunctionConcept).
         */
        template < class F, class G, class CheckF = funcy::Concepts::FunctionConceptCheck< F >,
                   class CheckG = funcy::Concepts::FunctionConceptCheck< G > >
        struct Sum : Chainer< Sum< F, G, CheckF, CheckG > >
        {
            /**
             * @brief Constructor
             * @param f_ initializer for F
             * @param g_ initializer for G
             */
            template < class InitF, class InitG >
            constexpr Sum( InitF&& f_, InitG&& g_ )
                : f( std::forward< InitF >( f_ ) ), g( std::forward< InitG >( g_ ) ),
                  value( funcy::add_via_traits( f(), g() ) )
            {
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( Arg&& x )
            {
                funcy::update_if_present( f, x );
                funcy::update_if_present( g, std::forward< Arg >( x ) );
                value = funcy::add_via_traits( f(), g() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( Arg&& x )
            {
                funcy::update_if_present< index >( f, x );
                funcy::update_if_present< index >( g, std::forward< Arg >( x ) );
                value = funcy::add_via_traits( f(), g() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return value;
            }

            /// First directional derivative.
            template < int id, class Arg,
                       class IndexedArg = funcy::IndexedType< std::decay_t< Arg >, id >,
                       class = std::enable_if_t< funcy::ComputeSum<
                           funcy::D1< F, IndexedArg >, funcy::D1< G, IndexedArg > >::present > >
            auto d1( Arg&& dx ) const
            {
                return funcy::ComputeSum< funcy::D1< F, IndexedArg >, funcy::D1< G, IndexedArg > >(
                    f, g, std::forward< Arg >( dx ) )();
            }

            /// Second directional derivative.
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = funcy::IndexedType< std::decay_t< ArgX >, idx >,
                       class IndexedArgY = funcy::IndexedType< std::decay_t< ArgY >, idy >,
                       class = std::enable_if_t<
                           funcy::ComputeSum< funcy::D2< F, IndexedArgX, IndexedArgY >,
                                             funcy::D2< G, IndexedArgX, IndexedArgY > >::present > >
            auto d2( ArgX&& dx, ArgY&& dy ) const
            {
                return funcy::ComputeSum< funcy::D2< F, IndexedArgX, IndexedArgY >,
                                         funcy::D2< G, IndexedArgX, IndexedArgY > >(
                    f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ) )();
            }

            /// Third directional derivative.
            template < int idx, int idy, int idz, class ArgX, class ArgY, class ArgZ,
                       class IndexedArgX = funcy::IndexedType< std::decay_t< ArgX >, idx >,
                       class IndexedArgY = funcy::IndexedType< std::decay_t< ArgY >, idy >,
                       class IndexedArgZ = funcy::IndexedType< std::decay_t< ArgZ >, idz >,
                       class = std::enable_if_t< funcy::ComputeSum<
                           funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                           funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >::present > >
            auto d3( ArgX&& dx, ArgY&& dy, ArgZ&& dz ) const
            {
                return funcy::ComputeSum< funcy::D3< F, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                         funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ > >(
                    f, g, std::forward< ArgX >( dx ), std::forward< ArgY >( dy ),
                    std::forward< ArgZ >( dz ) )();
            }

        private:
            F f;
            G g;
            funcy::decay_t< decltype(
                funcy::add_via_traits( std::declval< F >()(), std::declval< G >()() ) ) >
                value;
        };
    }
}
