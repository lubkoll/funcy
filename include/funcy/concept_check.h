#pragma once

#include <funcy/util/extract_rows_and_cols.h>
#include <funcy/util/static_checks.h>

namespace funcy
{
    namespace Concepts
    {
        /** @addtogroup ConceptCheck
         *  @{ */
        /// Static check if the requirements of CopyConcept are satisfied.
        template < class Arg >
        struct CopyConceptCheck
        {
            static_assert( std::is_copy_constructible< Arg >(),
                           "CopyConcept: Input types must be copy-constructible." );
        };

        /// Static check if the requirements of MultiplyWithArithmeticFromLeftConcept are satisfied.
        template < class Arg >
        struct MultiplyWithArithmeticFromLeftConceptCheck
        {
            static_assert(
                Concepts::Has::Free::multiplication< Arg, double >() ||
                    Concepts::Has::MemOp::inPlaceMultiplication< Arg, double >(),
                "MultiplyWithArithmeticFromLeftConcept: Input types must support multiplication "
                "with double from the left (operator*(double,const Arg&))" );
            static_assert( Concepts::Has::Free::multiplication< Arg, int >() ||
                               Concepts::Has::MemOp::inPlaceMultiplication< Arg, int >(),
                           "MultiplyWithArithmeticFromLeftConcept: Input types must support "
                           "multiplication with int from the left (operator*(int,const Arg&))" );
        };

        /// Static check if the requirements of SummationConcept are satisfied.
        template < class Arg >
        struct SummationConceptCheck
        {
            static_assert( Concepts::Has::Free::summation< Arg >() ||
                               Concepts::Has::MemOp::inPlaceSummation< Arg >(),
                           "SummationConcept: Input types must support summation (operator+(const "
                           "Arg&, const Arg&)" );
        };

        /// Static check if the requirements of MultiplicationConcept are satisfied.
        template < class Arg1, class Arg2 >
        struct MultiplicationConceptCheck
        {
            static_assert( Concepts::Has::Free::multiplication< Arg1, Arg2 >() ||
                               Concepts::Has::MemFn::rightmultiplyany< Arg1, Arg2 >() ||
                               Concepts::Has::MemOp::inPlaceMultiplication< Arg1, Arg2 >(),
                           "MultiplicationConcept: Input types must support multiplication "
                           "(operator*(const Arg&, const Arg&" );
        };

        /// Static check if the requirements of ArithmeticConcept are satisfied.
        template < class Arg >
        struct ArithmeticConceptCheck : CopyConceptCheck< Arg >,
                                        MultiplyWithArithmeticFromLeftConceptCheck< Arg >,
                                        SummationConceptCheck< Arg >
        {
        };

        /// Static check if the requirements of a matrix are satisfied.
        template < class Matrix >
        struct IsMatrix : ArithmeticConceptCheck< Matrix >
        {
            static_assert( Concepts::Has::MemOp::SquareBracketAccessForMatrix< Matrix >::value ||
                               Concepts::Has::MemOp::RoundBracketAccessForMatrix< Matrix >::value,
                           "MatrixConcept: Currently only matrices that allow access to their "
                           "elements via A[i][j] or A(i,j) are supported.\nYou may contact the "
                           "developer to ask for further access or provide your own patch." );
        };

        /// Static check if the requirements of a vector are satisfied.
        template < class Vector >
        struct IsVector : ArithmeticConceptCheck< Vector >
        {
            static_assert( Concepts::Has::MemOp::SquareBracketAccessForVector< Vector >::value ||
                               Concepts::Has::MemOp::RoundBracketAccessForVector< Vector >::value,
                           "VectorConcept: Currently only vectors that allow access to their "
                           "elements via v[i] or v(i) are supported.\nYou may contact the "
                           "developer to ask for further access or provide your own patch." );
        };
        /** @} */
    } // namespace Concepts
} // namespace funcy
