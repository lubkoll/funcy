#pragma once

#include "extract_rows_and_cols.h"
#include "type_traits.h"

#include <string>
#include <type_traits>
#include <utility>

namespace funcy
{
    namespace Concepts
    {
        /** @addtogroup ConceptGroup
         *  @{ */

        /// @cond
        template < class F >
        constexpr bool isFunction();

        namespace Try
        {
            namespace MemOp
            {
                template < class Arg >
                using InPlaceSummation = decltype( std::declval< Arg >() += std::declval< Arg >() );

                template < class Arg1, class Arg2 >
                using InPlaceMultiplication =
                    decltype( std::declval< Arg1 >() *= std::declval< Arg2 >() );

                template < class Matrix >
                using SquareBracketAccessForMatrix = decltype( std::declval< Matrix >()[ 0 ][ 0 ] );

                template < class Matrix >
                using RoundBracketAccessForMatrix = decltype( std::declval< Matrix >()( 0, 0 ) );

                template < class Vector >
                using SquareBracketAccessForVector = decltype( std::declval< Vector >()[ 0 ] );

                template < class Vector >
                using RoundBracketAccessForVector = decltype( std::declval< Vector >()( 0 ) );
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

                template < class Arg >
                using Summation = decltype( std::declval< Arg >() + std::declval< Arg >() );
            } // namespace Free
        }     // namespace Try
        /// @endcond

        namespace Has
        {
            namespace MemOp
            {
                template < class Matrix, class = void >
                struct SquareBracketAccessForMatrix : std::false_type
                {
                };

                template < class Matrix >
                struct SquareBracketAccessForMatrix<
                    Matrix, std::void_t< Try::MemOp::SquareBracketAccessForMatrix< Matrix > > >
                    : std::true_type
                {
                };

                template < class Matrix, class = void >
                struct RoundBracketAccessForMatrix : std::false_type
                {
                };

                template < class Matrix >
                struct RoundBracketAccessForMatrix<
                    Matrix, std::void_t< Try::MemOp::RoundBracketAccessForMatrix< Matrix > > >
                    : std::true_type
                {
                };

                template < class Vector, class = void >
                struct SquareBracketAccessForVector : std::false_type
                {
                };

                template < class Vector >
                struct SquareBracketAccessForVector<
                    Vector, std::void_t< Try::MemOp::SquareBracketAccessForVector< Vector > > >
                    : std::true_type
                {
                };

                template < class Vector, class = void >
                struct RoundBracketAccessForVector : std::false_type
                {
                };

                template < class Vector >
                struct RoundBracketAccessForVector<
                    Vector, std::void_t< Try::MemOp::RoundBracketAccessForVector< Vector > > >
                    : std::true_type
                {
                };

                template < class Arg, bool, class = void >
                struct InPlaceSummation : std::false_type
                {
                };

                template < class Arg >
                struct InPlaceSummation< Arg, true,
                                         std::void_t< Try::MemOp::InPlaceSummation< Arg > > >
                    : std::true_type
                {
                };

                template < class Arg1, class Arg2, bool, class = void >
                struct InPlaceMultiplication : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct InPlaceMultiplication<
                    Arg1, Arg2, true,
                    std::void_t< Try::MemOp::InPlaceMultiplication< Arg1, Arg2 > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of type Arg1 support in-place multiplication with objects of
                /// type Arg2.
                template < class Arg1, class Arg2 >
                constexpr bool inPlaceMultiplication()
                {
                    return InPlaceMultiplication < Arg1, Arg2,
                           !isFunction< Arg1 >() && !isFunction< Arg2 >() &&
                               !is_arithmetic< Arg1 >() > ::value;
                }

                /// Check if objects of type Arg support in-place summation.
                template < class Arg >
                constexpr bool inPlaceSummation()
                {
                    return InPlaceSummation < Arg,
                           !isFunction< Arg >() && !is_arithmetic< Arg >() > ::value;
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

                template < class Arg1, class Arg2, bool, class = void >
                struct Rightmultiplany : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct Rightmultiplany< Arg1, Arg2, true,
                                        std::void_t< Try::MemFn::rightmultiplyany< Arg1, Arg2 > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of type Arg1 support multiplication with objects of type Arg2
                /// via call to rightmultiplyany(Arg2).
                template < class Arg1, class Arg2 >
                constexpr bool rightmultiplyany()
                {
                    return Rightmultiplany < Arg1, Arg2,
                           !isFunction< Arg1 >() && !isFunction< Arg2 >() &&
                               !is_arithmetic< Arg1 >() && !is_arithmetic< Arg2 >() > ::value;
                }
            } // namespace MemFn

            namespace Free
            {
                /// @cond
                template < class Arg1, class Arg2,
                           bool =
                               !( is_arithmetic< Arg1 >::value && is_arithmetic< Arg2 >::value ) &&
                               !(std::is_invocable_v< Arg1 > || std::is_invocable_v< Arg2 >),
                           class = void >
                struct Multiplication : std::false_type
                {
                };

                template < class Arg1, class Arg2 >
                struct Multiplication< Arg1, Arg2, false, void > : std::true_type
                {
                };

                template < class Arg1, class Arg2 >
                struct Multiplication< Arg1, Arg2, true,
                                       std::void_t< Try::Free::Multiplication< Arg1, Arg2 > > >
                    : std::true_type
                {
                };

                template < class Arg, bool, class = void >
                struct Summation : std::false_type
                {
                };

                template < class Arg >
                struct Summation< Arg, true, std::void_t< Try::Free::Summation< Arg > > >
                    : std::true_type
                {
                };
                /// @endcond

                /// Check if objects of typed Arg1 and Arg2 support multiplication (free operator*).
                template < class Arg1, class Arg2 >
                constexpr bool multiplication()
                {
                    return Multiplication< Arg1, Arg2 >::value;
                }

                /// Check if objects of type Arg support summation.
                template < class Arg >
                constexpr bool summation()
                {
                    return Summation < Arg,
                           !isFunction< Arg >() && !is_arithmetic< Arg >() > ::value;
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
                       ( Has::MemFn::d2< F, IndexedArgX, IndexedArgY >::value
                             ? Has::MemFn::d1< F, IndexedArgX >::value
                             : true );
            }

            template < class F, class IndexedArgX, class IndexedArgY, class IndexedArgZ >
            constexpr bool consistentThirdDerivative()
            {
                return consistentSecondDerivative< F, IndexedArgX, IndexedArgY >() &&
                       ( Has::MemFn::d3< F, IndexedArgX, IndexedArgY, IndexedArgZ >::value
                             ? Has::MemFn::d2< F, IndexedArgX, IndexedArgY >::value
                             : true );
            }
        } // namespace Has

        template < class F >
        constexpr bool isFunction()
        {
            return std::is_invocable_v< F >;
        }
        /** @} */
    } // namespace Concepts
} // namespace funcy
