#pragma once

#include <funcy/util/traverse.hh>
#include <funcy/variable.hh>

#include <limits>
#include <string>
#include <type_traits>
#include <tuple>

namespace stringy
{
    /// @cond
    template < int, int >
    struct Variable;
    namespace concept
    {
        template < class >
        struct IsFunction;
    }

    namespace VariableDetail
    {
        template < class T, int k >
        struct ExtractReturnValue
        {
            static std::string apply( const T& x )
            {
                return x;
            }
        };

        template < int k, class... Args >
        struct ExtractReturnValue< std::tuple< Args... >, k >
        {
            static std::string apply( const std::tuple< Args... >& x )
            {
                return std::get< k >( x );
            }
        };
    }
    /// @endcond

    /// Independent variable. Can be uniquely identified by its id.
    template < int id, int k = 0 >
    struct Variable
    {
        static constexpr int ValueIdx = 0;
        static constexpr int DerivativeIdx = 1;

        Variable() = default;

        explicit Variable( const std::string& t_ ) : t( t_ )
        {
        }

        explicit Variable( std::string&& t_ ) : t( std::move( t_ ) )
        {
        }

        /// Update variable if index==id.
        template < int index >
        void update( const std::string& t_ )
        {
            t = t_;
        }

        /// Value of the variable.
        std::string operator()() const noexcept
        {
            return std::string( t ).append( "_{" ).append( std::to_string( id ) ).append( "}" );
        }

        /// First directional derivative. Only available if id==index.
        template < int index, class Arg, class = std::enable_if_t< id == index > >
        const std::string& d1( const Arg& dt ) const noexcept
        {
            return VariableDetail::ExtractReturnValue< Arg, k >::apply( dt )
                .append( "_{" )
                .append( std::to_string( id ) )
                .append( "}" );
        }

    private:
        std::string t;
    };

    /// Generate variable from input type.
    template < int id, int k = 0 >
    Variable< id, k > variable( const std::string& t )
    {
        return Variable< id, k >( t );
    }

    /// @cond
    namespace VariableDetail
    {
        /// Check if Type is variable.
        template < class >
        struct IsVariable : std::false_type
        {
        };

        template < int id, int k >
        struct IsVariable< Variable< id, k > > : std::true_type
        {
        };

        template < class, int >
        struct HasVariableWithId : std::false_type
        {
        };

        template < int id0, int id, int k >
        struct HasVariableWithId< Variable< id0, k >, id >
            : std::integral_constant< bool, id == id0 >
        {
        };

        namespace Has
        {
            /// Check if Type contains has variable.
            template < class F >
            using Variable = funcy::Meta::AnyOf< F, IsVariable >;

            template < class F, int id >
            struct VariableId
            {
                template < class G >
                struct HasVariable
                {
                    static constexpr bool value = HasVariableWithId< G, id >::value;
                };
                static constexpr bool value = funcy::Meta::AnyOf< F, HasVariable >::value;
            };
        }

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

        namespace Detail
        {
            template < class Type >
            struct MaxVariableId
                : std::integral_constant< int, std::numeric_limits< int >::lowest() >
            {
            };

            template < int id, int k >
            struct MaxVariableId< Variable< id, k > > : std::integral_constant< int, id >
            {
            };

            template < int id, int k >
            struct MaxVariableId< const Variable< id, k > > : std::integral_constant< int, id >
            {
            };

            template < class Type >
            struct MinVariableId : std::integral_constant< int, std::numeric_limits< int >::max() >
            {
            };

            template < int id, int k >
            struct MinVariableId< Variable< id, k > > : std::integral_constant< int, id >
            {
            };

            template < int id, int k >
            struct MinVariableId< const Variable< id, k > > : std::integral_constant< int, id >
            {
            };
        }

        template < class F >
        using MaxVariableId = funcy::Meta::Traverse< F, Detail::MaxVariableId, Max >;

        template < class F >
        using MinVariableId = funcy::Meta::Traverse< F, Detail::MinVariableId, Min >;
    }
    /// @endcond

    /// Get underlying type of variable with index id.
    template < class F, int id >
    using Variable_t = std::string;

    namespace concept
    {
        /** @addtogroup ConceptCheck
             *  @{ */

        /// Check if T is of type Variable<Type,n>.
        template < class T >
        constexpr bool isVariable()
        {
            return VariableDetail::IsVariable< T >::value;
        }

        namespace Has
        {
            /// Check if T contains a type Variable<Type,n>.
            template < class T >
            constexpr bool variable()
            {
                return VariableDetail::Has::Variable< std::decay_t< T > >::value;
            }

            /// Check if T contains a type Variable<Type,id>.
            template < class T, int id >
            constexpr bool variableId()
            {
                return VariableDetail::Has::VariableId< std::decay_t< T >, id >::value;
            }

            /// Check if T contains at least two variables.
            template < class T >
            constexpr bool moreThanOneVariable()
            {
                return VariableDetail::MinVariableId< std::decay_t< T > >::value <
                       VariableDetail::MaxVariableId< std::decay_t< T > >::value;
            }
        }

        /// Check if variable with index id has type Type.
        template < class F, class Type, int id >
        constexpr bool checkArgument()
        {
            return funcy::ContainsType< Variable_t< F, id >, Type >::value;
        }

        /** @} */
    }
}
