#pragma once

#include <funcy/util/chainer.h>

#include <texy/concepts.h>
#include <texy/util/string.h>
#include <type_traits>

namespace texy
{
    namespace linalg
    {
        /** @addtogroup TexifyLinearAlgebraGroup
         *  @{ */
        /// Represents transposition matrices.
        class Transpose : public funcy::Chainer< Transpose >
        {
        public:
            explicit Transpose( const std::string& A ) : A( A )
            {
            }

            void update( const std::string& A )
            {
                this->A = A;
            }

            std::string d0() const noexcept
            {
                return addStrictScope( A ).append( "^T" );
            }

            std::string d1( const std::string& dA ) const
            {
                return addStrictScope( dA ).append( "^T" );
            }

        private:
            std::string A;
        };

        inline auto transpose( const std::string& A )
        {
            return Transpose( A );
        }

        template < Function F >
        auto transpose( const F& f )
        {
            return Transpose( f() )( f );
        }
        /** @} */
    } // namespace linalg
} // namespace texy
