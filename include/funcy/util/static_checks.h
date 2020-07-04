#pragma once

#include <funcy/concepts.h>
#include <funcy/util/extract_rows_and_cols.h>
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
            namespace mem_op
            {
                template < class Arg >
                using InPlaceSummation = decltype( std::declval< Arg >() += std::declval< Arg >() );

                template < class Arg1, class Arg2 >
                using InPlaceMultiplication =
                    decltype( std::declval< Arg1 >() *= std::declval< Arg2 >() );
            } // namespace mem_op

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

                template < class Arg1, class Arg2 >
                using rightmultiplyany =
                    decltype( std::declval< Arg1 >().rightmultiplyany( std::declval< Arg2 >() ) );

            } // namespace mem_fn

            namespace fun
            {
                template < class Arg1, class Arg2 >
                using Multiplication = decltype( std::declval< Arg1 >() * std::declval< Arg2 >() );
            } // namespace fun
        }     // namespace test
        /// @endcond

        namespace has
        {
            namespace mem_op
            {
                template < class Arg, class = void >
                struct InPlaceSummation : std::false_type
                {
                };

                template < class Arg >
                struct InPlaceSummation< Arg, std::void_t< test::mem_op::InPlaceSummation< Arg > > >
                    : std::true_type
                {
                };

                template < class Arg1, class Arg2, class = void >
                struct InPlaceMultiplication : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct InPlaceMultiplication<
                    Arg1, Arg2, std::void_t< test::mem_op::InPlaceMultiplication< Arg1, Arg2 > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of type Arg1 support in-place multiplication with objects of
                /// type Arg2.
                template < class Arg1, class Arg2 >
                constexpr bool in_place_product() requires( !Function< Arg1 > &&
                                                            !Function< Arg2 > &&
                                                            !Arithmetic< Arg1 > )
                {
                    return InPlaceMultiplication< Arg1, Arg2 >::value;
                }

                template < class Arg1, class Arg2 >
                constexpr bool in_place_product()
                {
                    return false;
                }

                /// Check if objects of type Arg support in-place summation.
                template < class Arg >
                constexpr bool in_place_sum() requires( !Function< Arg > && !Arithmetic< Arg > )
                {
                    return InPlaceSummation< Arg >::value;
                }

                /// Check if objects of type Arg support in-place summation.
                template < class Arg >
                constexpr bool in_place_sum()
                {
                    return false;
                }
            } // namespace mem_op

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

                template < class Arg1, class Arg2, class = void >
                struct Rightmultiplany : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct Rightmultiplany<
                    Arg1, Arg2, std::void_t< test::mem_fn::rightmultiplyany< Arg1, Arg2 > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of type Arg1 support multiplication with objects of type Arg2
                /// via call to rightmultiplyany(Arg2).
                template < class Arg1, class Arg2 >
                constexpr bool
                rightmultiplyany() requires( !Function< Arg1 > && !Function< Arg2 > &&
                                             !Arithmetic< Arg1 > && !Arithmetic< Arg2 > )
                {
                    return Rightmultiplany< Arg1, Arg2 >::value;
                }

                /// Check if objects of type Arg1 support multiplication with objects of type Arg2
                /// via call to rightmultiplyany(Arg2).
                template < class Arg1, class Arg2 >
                constexpr bool rightmultiplyany()
                {
                    return false;
                }
            } // namespace mem_fn

            namespace fun
            {
                /// @cond
                namespace detail
                {
                    template < class T, class S >
                    constexpr bool product() requires requires( T t, S s )
                    {
                        { t * s };
                    }
                    {
                        return true;
                    }

                    template < class T >
                    constexpr bool product()
                    {
                        return false;
                    }

                    template < class T >
                    constexpr bool sum() requires requires( T t )
                    {
                        { t + t };
                    }
                    {
                        return true;
                    }

                    template < class T >
                    constexpr bool sum()
                    {
                        return false;
                    }
                } // namespace detail
                /// @endcond

                /// Check if objects of typed Arg1 and Arg2 support multiplication (free operator*).
                template < class T, class S >
                constexpr bool multiplication() requires( !Function< T > && !Function< S > &&
                                                          !Arithmetic< T > && !Arithmetic< S > )
                {
                    return detail::product< T, S >();
                }

                /// Check if objects of typed Arg1 and Arg2 support multiplication (free operator*).
                template < class Arg1, class Arg2 >
                constexpr bool multiplication()
                {
                    return false;
                }

                /// Check if objects of type Arg support summation.
                template < class T >
                constexpr bool summation() requires( !Function< T > && !Arithmetic< T > )
                {
                    return detail::sum< T >();
                }

                /// Check if objects of type Arg support summation.
                template < class Arg >
                constexpr bool summation()
                {
                    return false;
                }
            } // namespace fun

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
