#pragma once

#include <type_traits>
#include <utility>

#include <funcy/concept_check.hh>
#include <funcy/util/compute_chain.hh>
#include <funcy/util/compute_sum.hh>
#include <funcy/util/derivative_wrappers.hh>
#include <funcy/util/evaluate_if_present.hh>
#include <funcy/util/indexed_type.hh>

namespace texy
{
    /// @cond
    template < class >
    struct Chainer;
    /// @endcond

    namespace mathop
    {
        /**
         * @ingroup TexifyMathematicalOperationsGroup
         *
         * @brief %Chain \f$ f\circ g \f$ of functions \f$f\f$ and \f$g\f$ of type F resp. G (F and
         * G must satisfy the requirements of concept::FunctionConcept).
         */
        template < class F, class G, class = funcy::concept::IsFunction< F >,
                   class = funcy::concept::IsFunction< G > >
        struct Chain : Chainer< Chain< F, G, funcy::concept::IsFunction< F >,
                                       funcy::concept::IsFunction< G > > >
        {
        private:
            using FArg = decltype( std::declval< G >()() );

            template < class IndexedArgX, class IndexedArgY, class IndexedFArgX,
                       class IndexedFArgY >
            using D2LazyType = funcy::ComputeSum<
                funcy::ComputeChainD2< F, funcy::D1< G, IndexedArgX >, funcy::D1< G, IndexedArgY >,
                                      IndexedFArgX, IndexedFArgY >,
                funcy::ComputeChainD1< F, funcy::D2< G, IndexedArgX, IndexedArgY >, IndexedFArgX > >;

            template < class IndexedArgX, class IndexedArgY, class IndexedArgZ, class IndexedFArgX,
                       class IndexedFArgY, class IndexedFArgZ >
            using D3LazyType = funcy::ComputeSum<
                funcy::ComputeChainD3< F, funcy::D1< G, IndexedArgX >, funcy::D1< G, IndexedArgY >,
                                      funcy::D1< G, IndexedArgZ >, IndexedFArgX, IndexedFArgY,
                                      IndexedFArgZ >,
                funcy::ComputeChainD2< F, funcy::D2< G, IndexedArgX, IndexedArgZ >,
                                      funcy::D1< G, IndexedArgY >, IndexedFArgX, IndexedFArgY >,
                funcy::ComputeChainD2< F, funcy::D1< G, IndexedArgX >,
                                      funcy::D2< G, IndexedArgY, IndexedArgZ >, IndexedFArgX,
                                      IndexedFArgY >,
                funcy::ComputeChainD2< F, funcy::D2< G, IndexedArgX, IndexedArgY >,
                                      funcy::D1< G, IndexedArgZ >, IndexedFArgX, IndexedFArgZ >,
                funcy::ComputeChainD1< F, funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ >,
                                      IndexedFArgX > >;

        public:
            /**
             * @brief Constructor taking copies of the functions to be chained.
             * @param f_ outer function
             * @param g_ inner function
             */
            constexpr Chain( const F& f_, const G& g_ ) : g( g_ ), f( f_ )
            {
                funcy::update_if_present( f, g() );
            }

            /**
             * @brief Constructor taking moving the functions to be chained.
             * @param f_ outer function
             * @param g_ inner function
             */
            constexpr Chain( F&& f_, G&& g_ ) : g( std::move( g_ ) ), f( std::move( f_ ) )
            {
                funcy::update_if_present( f, g() );
            }

            /// Update point of evaluation.
            template < class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present( g, x );
                funcy::update_if_present( f, g() );
            }

            /// Update variable corresponding to index.
            template < int index, class Arg >
            void update( const Arg& x )
            {
                funcy::update_if_present< index >( g, x );
                funcy::update_if_present( f, g() );
            }

            /// Function value.
            constexpr decltype( auto ) d0() const noexcept
            {
                return f();
            }

            /**
             * @brief First directional derivative.
             * @param dx direction for which the derivative is computed
             */
            template < int id, class Arg, class IndexedArg = funcy::IndexedType< Arg, id >,
                       class IndexedFArg = funcy::IndexedType< FArg, id >,
                       class = std::enable_if_t< funcy::ComputeChainD1< F, funcy::D1< G, IndexedArg >,
                                                                       IndexedFArg >::present > >
            auto d1( Arg const& dx ) const
            {
                return funcy::chain< IndexedFArg >( f, funcy::D1< G, IndexedArg >( g, dx ) )();
            }

            /**
             * @brief Second directional derivative.
             * @param dx direction for which the derivative is computed
             * @param dy direction for which the derivative is computed
             */
            template < int idx, int idy, class ArgX, class ArgY,
                       class IndexedArgX = funcy::IndexedType< ArgX, idx >,
                       class IndexedArgY = funcy::IndexedType< ArgY, idy >,
                       class IndexedFArgX = funcy::IndexedType< FArg, idx >,
                       class IndexedFArgY = funcy::IndexedType< FArg, idy >,
                       class = std::enable_if_t< D2LazyType< IndexedArgX, IndexedArgY, IndexedFArgX,
                                                             IndexedFArgY >::present > >
            auto d2( ArgX const& dx, ArgY const& dy ) const
            {
                return funcy::sum( funcy::chain< IndexedFArgX, IndexedFArgY >(
                                      f, funcy::D1< G, IndexedArgX >( g, dx ),
                                      funcy::D1< G, IndexedArgY >( g, dy ) ),
                                  funcy::chain< IndexedFArgX >(
                                      f, funcy::D2< G, IndexedArgX, IndexedArgY >( g, dx, dy ) ) )();
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
                       class IndexedFArgX = funcy::IndexedType< FArg, idx >,
                       class IndexedFArgY = funcy::IndexedType< FArg, idy >,
                       class IndexedFArgZ = funcy::IndexedType< FArg, idz >,
                       class = std::enable_if_t<
                           D3LazyType< IndexedArgX, IndexedArgY, IndexedArgZ, IndexedFArgX,
                                       IndexedFArgY, IndexedFArgZ >::present > >
            auto d3( ArgX const& dx, ArgY const& dy, ArgZ const& dz ) const
            {
                funcy::D1< G, IndexedArgX > dGdx( g, dx );
                funcy::D1< G, IndexedArgY > dGdy( g, dy );
                funcy::D1< G, IndexedArgZ > dGdz( g, dz );
                return funcy::sum(
                    funcy::chain< IndexedFArgX, IndexedFArgY, IndexedFArgZ >( f, dGdx, dGdy, dGdz ),
                    funcy::chain< IndexedFArgX, IndexedFArgY >(
                        f, funcy::D2< G, IndexedArgX, IndexedArgZ >( g, dx, dz ), dGdy ),
                    funcy::chain< IndexedFArgX, IndexedFArgY >(
                        f, dGdx, funcy::D2< G, IndexedArgY, IndexedArgZ >( g, dy, dz ) ),
                    funcy::chain< IndexedFArgX, IndexedFArgZ >(
                        f, funcy::D2< G, IndexedArgX, IndexedArgY >( g, dx, dy ), dGdz ),
                    funcy::chain< IndexedFArgX >(
                        f,
                        funcy::D3< G, IndexedArgX, IndexedArgY, IndexedArgZ >( g, dx, dy, dz ) ) )();
            }

        private:
            G g;
            F f;
        };
    }
}
