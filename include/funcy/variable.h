#pragma once

#include <funcy/concepts.h>
#include <funcy/util/traverse.h>

#include <limits>
#include <tuple>
#include <type_traits>

namespace funcy
{
    /// @cond
    template < class, int >
    struct Variable;

    template < class T, class Other >
    struct ContainsType : std::false_type
    {
    };

    template < class T >
    struct ContainsType< T, T > : std::true_type
    {
    };

    template < class T, class Gradient >
    struct ContainsType< T, std::tuple< T, Gradient > > : std::true_type
    {
    };

    template < class T, class Value >
    struct ContainsType< T, std::tuple< Value, T > > : std::true_type
    {
    };

    namespace detail
    {
        template < class Arg, class Extended >
        struct Assign;

        template < class Arg, class Gradient >
        struct Assign< Arg, std::tuple< Arg, Gradient > >
        {
            static auto apply( Arg& t, const std::tuple< Arg, Gradient >& x )
            {
                t = std::get< 0 >( x );
            }
        };

        template < class Arg, class Value >
        struct Assign< Arg, std::tuple< Value, Arg > >
        {
            static auto apply( Arg& t, const std::tuple< Value, Arg >& x )
            {
                t = std::get< 1 >( x );
            }
        };

        template < class Arg >
        struct Assign< Arg, Arg >
        {
            static void apply( Arg& t, const Arg& x )
            {
                t = x;
            }
        };

        template < class T, class Other >
        struct ExtractReturnValue;

        template < class T >
        struct ExtractReturnValue< T, T >
        {
            static const T& apply( const T& x )
            {
                return x;
            }
        };

        template < class T, class Gradient >
        struct ExtractReturnValue< T, std::tuple< T, Gradient > >
        {
            static const T& apply( const std::tuple< T, Gradient >& x )
            {
                return std::get< 0 >( x );
            }
        };

        template < class T, class Value >
        struct ExtractReturnValue< T, std::tuple< Value, T > >
        {
            static const T& apply( const std::tuple< Value, T >& x )
            {
                return std::get< 1 >( x );
            }
        };

        template < bool >
        struct Update
        {
            template < class T, class Arg >
            static void apply( T& t, const Arg& x )
            {
                Assign< T, Arg >::apply( t, x );
            }
        };

        template <>
        struct Update< false >
        {
            template < class T, class Arg >
            static void apply( const T&, const Arg& )
            {
            }
        };
    } // namespace detail
    /// @endcond

    /// Independent variable. Can be uniquely identified by its id.
    template < class T, int id >
    struct Variable
    {
        Variable() = default;

        constexpr explicit Variable( const T& t_ ) : t( t_ )
        {
        }

        constexpr explicit Variable( T&& t_ ) : t( std::move( t_ ) )
        {
        }

        /// Update variable if index==id.
        template < int index, class Arg >
        void update( const Arg& t_ )
        {
            detail::Update< index == id >::apply( t, t_ );
        }

        /// Value of the variable.
        constexpr const T& operator()() const noexcept
        {
            return t;
        }

        /// First directional derivative. Only available if id==index.
        template < int index, class Arg, class = std::enable_if_t< id == index > >
        const T& d1( const Arg& dt ) const noexcept
        {
            return detail::ExtractReturnValue< T, Arg >::apply( dt );
        }

    private:
        T t;
    };

    /// Generate variable from input type.
    template < int id, class T >
    Variable< T, id > variable( const T& t )
    {
        return Variable< T, id >( t );
    }

    /// @cond
    namespace detail
    {
        /// Check if Type is variable.
        template < class >
        struct IsVariable : std::false_type
        {
        };

        template < class T, int n >
        struct IsVariable< Variable< T, n > > : std::true_type
        {
        };

        template < class, int >
        struct HasVariableWithId : std::false_type
        {
        };

        template < class Type, int id0, int id >
        struct HasVariableWithId< funcy::Variable< Type, id0 >, id >
            : std::integral_constant< bool, id == id0 >
        {
        };

        namespace has
        {
            /// Check if Type contains has variable.
            template < Function F >
            using Variable = meta::AnyOf< F, IsVariable >;

            template < class F, int id >
            struct VariableId
            {
                template < class G >
                struct HasVariable
                {
                    static constexpr bool value = HasVariableWithId< G, id >::value;
                };
                static constexpr bool value = meta::AnyOf< F, HasVariable >::value;
            };
        } // namespace has

        constexpr bool greater( int a, int b )
        {
            return a > b;
        }

        template < class F, class G >
        struct Max
            : std::integral_constant< int, greater( F::value, G::value ) ? F::value : G::value >
        {
        };

        template < class F, class G >
        struct Min
            : std::integral_constant< int, greater( G::value, F::value ) ? F::value : G::value >
        {
        };

        namespace detail
        {
            template < class Type >
            struct MaxVariableId
                : std::integral_constant< int, std::numeric_limits< int >::lowest() >
            {
            };

            template < class T, int id >
            struct MaxVariableId< funcy::Variable< T, id > > : std::integral_constant< int, id >
            {
            };

            template < class T, int id >
            struct MaxVariableId< const funcy::Variable< T, id > >
                : std::integral_constant< int, id >
            {
            };

            template < class Type >
            struct MinVariableId : std::integral_constant< int, std::numeric_limits< int >::max() >
            {
            };

            template < class T, int id >
            struct MinVariableId< funcy::Variable< T, id > > : std::integral_constant< int, id >
            {
            };

            template < class T, int id >
            struct MinVariableId< const funcy::Variable< T, id > >
                : std::integral_constant< int, id >
            {
            };
        } // namespace detail

        template < class F >
        using MaxVariableId = meta::Traverse< F, detail::MaxVariableId, Max >;

        template < class F >
        using MinVariableId = meta::Traverse< F, detail::MinVariableId, Min >;

        template < class F, int id >
        struct VariableType
        {
            using type = void;
        };

        template < template < Function > class G, Function F, int id >
        struct VariableType< G< F >, id >
        {
            using type = typename VariableType< F, id >::type;
        };

        template < template < Function, Function > class H, Function F, Function G, int id >
        struct VariableType< H< F, G >, id >
        {
            using type = std::conditional_t<
                std::is_same< void, typename VariableType< F, id >::type >::value,
                typename VariableType< G, id >::type, typename VariableType< F, id >::type >;
        };

        template < class T, int id >
        struct VariableType< Variable< T, id >, id >
        {
            using type = T;
        };

        template < class T, int id >
        struct VariableType< const Variable< T, id >, id >
        {
            using type = T;
        };

        template < class, class >
        struct ChooseTypeImpl;

        template < class T >
        struct ChooseTypeImpl< T, void >
        {
            using type = T;
        };

        template < class T >
        struct ChooseTypeImpl< void, T >
        {
            using type = T;
        };

        template <>
        struct ChooseTypeImpl< void, void >
        {
            using type = void;
        };

        template < class F, class G >
        struct ChooseType
        {
            using type = typename ChooseTypeImpl< typename F::type, typename G::type >::type;
        };
    } // namespace detail
    /// @endcond

    /// Get underlying type of variable with index id.
    template < class F, int id >
    using Variable_t = typename detail::VariableType< std::decay_t< F >, id >::type;

    namespace static_check
    {
        /** @addtogroup ConceptCheck
         *  @{ */
        namespace has
        {
            /// Check if T contains a type Variable<Type,n>.
            template < Function T >
            constexpr bool variable()
            {
                return detail::has::Variable< std::decay_t< T > >::value;
            }

            /// Check if T contains a type Variable<Type,id>.
            template < class T, int id >
            constexpr bool variable_id()
            {
                return detail::has::VariableId< std::decay_t< T >, id >::value;
            }
        } // namespace has

        /// Check if variable with index id has type Type.
        template < class F, class Type, int id >
        constexpr bool check_argument()
        {
            return ContainsType< Variable_t< F, id >, Type >::value;
        }

        /** @} */
    } // namespace static_check
} // namespace funcy
