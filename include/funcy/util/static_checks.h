#pragma once

#include "extract_rows_and_cols.h"
#include "type_traits.h"

#include <funcy/concepts.h>

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
        namespace Try
        {
            namespace MemOp
            {
                template < class Arg >
                using InPlaceSummation = decltype( std::declval< Arg >() += std::declval< Arg >() );

                template < class Arg1, class Arg2 >
                using InPlaceMultiplication =
                    decltype( std::declval< Arg1 >() *= std::declval< Arg2 >() );
            } // namespace MemOp

            namespace MemFn
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

            } // namespace MemFn

            namespace Free
            {
                template < class Arg1, class Arg2 >
                using Multiplication = decltype( std::declval< Arg1 >() * std::declval< Arg2 >() );
            } // namespace Free
        }     // namespace Try
        /// @endcond

        namespace has
        {
            namespace MemOp
            {
                template < class Arg, class = void >
                struct InPlaceSummation : std::false_type
                {
                };

                template < class Arg >
                struct InPlaceSummation< Arg, std::void_t< Try::MemOp::InPlaceSummation< Arg > > >
                    : std::true_type
                {
                };

                template < class Arg1, class Arg2, class = void >
                struct InPlaceMultiplication : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct InPlaceMultiplication<
                    Arg1, Arg2, std::void_t< Try::MemOp::InPlaceMultiplication< Arg1, Arg2 > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of type Arg1 support in-place multiplication with objects of
                /// type Arg2.
                template < class Arg1, class Arg2 >
                constexpr bool inPlaceMultiplication() requires( !Function< Arg1 > &&
                                                                 !Function< Arg2 > &&
                                                                 !Arithmetic< Arg1 > )
                {
                    return InPlaceMultiplication< Arg1, Arg2 >::value;
                }

                template < class Arg1, class Arg2 >
                constexpr bool inPlaceMultiplication()
                {
                    return false;
                }

                /// Check if objects of type Arg support in-place summation.
                template < class Arg >
                constexpr bool inPlaceSummation() requires( !Function< Arg > && !Arithmetic< Arg > )
                {
                    return InPlaceSummation< Arg >::value;
                }

                /// Check if objects of type Arg support in-place summation.
                template < class Arg >
                constexpr bool inPlaceSummation()
                {
                    return false;
                }
            } // namespace MemOp

            namespace MemFn
            {
                /// @cond
                template < class F, class IndexedArg, class = void >
                struct d1 : std::false_type
                {
                };

                template < class F, class IndexedArg >
                struct d1< F, IndexedArg, std::void_t< Try::MemFn::d1< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArg >
                struct d1< F, IndexedArg,
                           std::void_t< Try::MemFn::d1_without_index< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class = void >
                struct d2 : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2< F, IndexedArgX, IndexedArgY,
                           std::void_t< Try::MemFn::d2< F, IndexedArgX, IndexedArgY > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2<
                    F, IndexedArgX, IndexedArgY,
                    std::void_t< Try::MemFn::d2_without_index< F, IndexedArgX, IndexedArgY > > >
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
                    std::void_t< Try::MemFn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
                struct d3< F, IndexedArgX, IndexedArgY, IndexedArgZ,
                           std::void_t< Try::MemFn::d3_without_index< F, IndexedArgX, IndexedArgY,
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
                                      std::void_t< Try::MemFn::d1< F, IndexedArg > > >
                    : std::true_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY, class = void >
                struct d2_with_index : std::false_type
                {
                };

                template < class F, class IndexedArgX, class IndexedArgY >
                struct d2_with_index< F, IndexedArgX, IndexedArgY,
                                      std::void_t< Try::MemFn::d2< F, IndexedArgX, IndexedArgY > > >
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
                    std::void_t< Try::MemFn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ > > >
                    : std::true_type
                {
                };

                template < class Arg1, class Arg2, class = void >
                struct Rightmultiplany : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct Rightmultiplany< Arg1, Arg2,
                                        std::void_t< Try::MemFn::rightmultiplyany< Arg1, Arg2 > > >
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
            } // namespace MemFn

            namespace Free
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
            } // namespace Free

            namespace NestedType
            {
                /// @cond
                template < class EigenArg, class = void >
                struct PlainObject : std::false_type
                {
                };
                template < class EigenArg >
                struct PlainObject< EigenArg,
                                    std::void_t< Try::NestedType::PlainObject< EigenArg > > >
                    : std::true_type
                {
                };
                /// @endcond
            } // namespace NestedType

            template < class F >
            constexpr bool consistentFirstDerivative()
            {
                return std::is_invocable_v< F >;
            }

            template < class F, class IndexedArgX, class IndexedArgY >
            constexpr bool consistentSecondDerivative()
            {
                return consistentFirstDerivative< F >() &&
                       ( has::MemFn::d2< F, IndexedArgX, IndexedArgY >::value
                             ? has::MemFn::d1< F, IndexedArgX >::value
                             : true );
            }

            template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
            constexpr bool consistentThirdDerivative()
            {
                return consistentSecondDerivative< F, IndexedArgX, IndexedArgY >() &&
                       ( has::MemFn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value
                             ? has::MemFn::d2< F, IndexedArgX, IndexedArgY >::value
                             : true );
            }
        } // namespace has
        /** @} */
    } // namespace static_check
} // namespace funcy
