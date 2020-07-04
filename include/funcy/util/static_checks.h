#pragma once

#include <funcy/concepts.h>
#include <funcy/util/type_traits.h>

#include <string>
#include <type_traits>
#include <utility>

namespace funcy
{
    namespace static_check
    {
        /** @addtogroup ConceptGroup
         *  @{ */

        /// @cond
        namespace test
        {
            namespace mem_fn
            {
                template < class F, class IndexedArg, class Arg = typename IndexedArg::type,
                           int id = IndexedArg::index >
                using d1 =
                    decltype( std::declval< F >().template d1< id >( std::declval< Arg >() ) );

                template < class F, class IndexedArg, class Arg = typename IndexedArg::type >
                using d1_without_index =
                    decltype( std::declval< F >().d1( std::declval< Arg >() ) );

                template < class F, class IndexedArgX, class IndexedArgY,
                           class ArgX = typename IndexedArgX::type,
                           class ArgY = typename IndexedArgY::type, int idx = IndexedArgX::index,
                           int idy = IndexedArgY::index >
                using d2 = decltype( std::declval< F >().template d2< idx, idy >(
                    std::declval< ArgX >(), std::declval< ArgY >() ) );

                template < class F, class IndexedArgX, class IndexedArgY,
                           class ArgX = typename IndexedArgX::type,
                           class ArgY = typename IndexedArgY::type >
                using d2_without_index = decltype(
                    std::declval< F >().d2( std::declval< ArgX >(), std::declval< ArgY >() ) );

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
                           class ArgX = typename IndexedArgX::type,
                           class ArgY = typename IndexedArgY::type,
                           class ArgZ = typename IndexedArgZ::type, int idx = IndexedArgX::index,
                           int idy = IndexedArgY::index, int idz = IndexedArgZ::index >
                using d3 = decltype( std::declval< F >().template d3< idx, idy, idz >(
                    std::declval< ArgX >(), std::declval< ArgY >(), std::declval< ArgZ >() ) );

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
                           class ArgX = typename IndexedArgX::type,
                           class ArgY = typename IndexedArgY::type,
                           class ArgZ = typename IndexedArgZ::type >
                using d3_without_index = decltype( std::declval< F >().d3(
                    std::declval< ArgX >(), std::declval< ArgY >(), std::declval< ArgZ >() ) );

            } // namespace mem_fn
        }     // namespace test
        /// @endcond

        namespace has
        {
            namespace mem_fn
            {
                /// @cond
                template < class F, class IndexedArg, class = void >
                struct d1 : std::false_type
                {
                };

                template < class F, class IndexedArg >
                struct d1< F, IndexedArg, std::void_t< test::mem_fn::d1< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArg >
                struct d1< F, IndexedArg,
                           std::void_t< test::mem_fn::d1_without_index< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class = void >
                struct d2 : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2< F, IndexedArgX, IndexedArgY,
                           std::void_t< test::mem_fn::d2< F, IndexedArgX, IndexedArgY > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2<
                    F, IndexedArgX, IndexedArgY,
                    std::void_t< test::mem_fn::d2_without_index< F, IndexedArgX, IndexedArgY > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
                           class = void >
                struct d3 : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
                struct d3<
                    F, IndexedArgX, IndexedArgY, IndexedArgZ,
                    std::void_t< test::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
                struct d3< F, IndexedArgX, IndexedArgY, IndexedArgZ,
                           std::void_t< test::mem_fn::d3_without_index< F, IndexedArgX, IndexedArgY,
                                                                        IndexedArgZ > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArg, class = void >
                struct d1_with_index : std::false_type
                {
                };

                template < class F, class IndexedArg >
                struct d1_with_index< F, IndexedArg,
                                      std::void_t< test::mem_fn::d1< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class = void >
                struct d2_with_index : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2_with_index<
                    F, IndexedArgX, IndexedArgY,
                    std::void_t< test::mem_fn::d2< F, IndexedArgX, IndexedArgY > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ,
                           class = void >
                struct d3_with_index : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
                struct d3_with_index<
                    F, IndexedArgX, IndexedArgY, IndexedArgZ,
                    std::void_t< test::mem_fn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ > > >
                    : std::true_type
                {
                };
                /// @endcond
            } // namespace mem_fn

            namespace nested_type
            {
                /// @cond
                template < class EigenArg, class = void >
                struct PlainObject : std::false_type
                {
                };
                template < class EigenArg >
                struct PlainObject< EigenArg,
                                    std::void_t< test::nested_type::PlainObject< EigenArg > > >
                    : std::true_type
                {
                };
                /// @endcond
            } // namespace nested_type
        }     // namespace has
        /** @} */
    } // namespace static_check
} // namespace funcy
