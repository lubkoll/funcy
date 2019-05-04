// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_CONCEPT_CHECK_HH
#define FUNCY_CONCEPT_CHECK_HH

#include "funcy/util/extract_rows_and_cols.hh"
#include "funcy/util/static_checks.hh"

namespace funcy
{
  namespace concept
  {
    /** @addtogroup ConceptCheck
     *  @{ */
    /// Static check if the requirements of CopyConcept are satisfied.
    template < class Arg >
    struct CopyConceptCheck
    {
      static_assert(std::is_copy_constructible<Arg>(), "CopyConcept: Input types must be copy-constructible.");
    };


    /// Static check if the requirements of MultiplyWithArithmeticFromLeftConcept are satisfied.
    template < class Arg >
    struct MultiplyWithArithmeticFromLeftConceptCheck
    {
      static_assert(concept::Has::Free::multiplication< Arg , double > () ||
                    concept::Has::MemOp::inPlaceMultiplication< Arg , double >(),
                    "MultiplyWithArithmeticFromLeftConcept: Input types must support multiplication with double from the left (operator*(double,const Arg&))");
      static_assert(concept::Has::Free::multiplication< Arg , int > () ||
                    concept::Has::MemOp::inPlaceMultiplication< Arg , int >(),
                    "MultiplyWithArithmeticFromLeftConcept: Input types must support multiplication with int from the left (operator*(int,const Arg&))");
    };


    /// Static check if the requirements of SummationConcept are satisfied.
    template < class Arg >
    struct SummationConceptCheck
    {
      static_assert(concept::Has::Free::summation< Arg >() ||
                    concept::Has::MemOp::inPlaceSummation< Arg >(),
                    "SummationConcept: Input types must support summation (operator+(const Arg&, const Arg&)");
    };


    /// Static check if the requirements of MultiplicationConcept are satisfied.
    template < class Arg1 , class Arg2 >
    struct MultiplicationConceptCheck
    {
      static_assert(concept::Has::Free::multiplication< Arg1 , Arg2 >() ||
                    concept::Has::MemFn::rightmultiplyany< Arg1 , Arg2 >() ||
                    concept::Has::MemOp::inPlaceMultiplication< Arg1 , Arg2 >(),
                    "MultiplicationConcept: Input types must support multiplication (operator*(const Arg&, const Arg&");
    };


    /// Static check if the requirements of ArithmeticConcept are satisfied.
    template <class Arg>
    struct ArithmeticConceptCheck :
        CopyConceptCheck<Arg> ,
        MultiplyWithArithmeticFromLeftConceptCheck<Arg> ,
        SummationConceptCheck<Arg>
    {};


    /// Static check if the requirements of MatrixConcept are satisfied.
    template < class Matrix >
    struct IsMatrix : ArithmeticConceptCheck<Matrix>
    {
      static_assert(concept::Has::MemOp::SquareBracketAccessForMatrix<Matrix>::value ||
                    concept::Has::MemOp::RoundBracketAccessForMatrix<Matrix>::value,
                    "MatrixConcept: Currently only matrices that allow access to their elements via A[i][j] or A(i,j) are supported.\nYou may contact the developer to ask for further access or provide your own patch.");
    };


    /// Static check if the requirements of VectorConcept are satisfied.
    template < class Vector >
    struct IsVector : ArithmeticConceptCheck<Vector>
    {
      static_assert(concept::Has::MemOp::SquareBracketAccessForVector<Vector>::value ||
                    concept::Has::MemOp::RoundBracketAccessForVector<Vector>::value,
                    "VectorConcept: Currently only vectors that allow access to their elements via v[i] or v(i) are supported.\nYou may contact the developer to ask for further access or provide your own patch.");
    };

    /// Static check if the requirements of SquareMatrixConcept are satisfied.
    template < class Matrix >
    struct SquareIsMatrix : IsMatrix<Matrix>, MultiplicationConceptCheck<Matrix,Matrix>
    {
      /// Require symmetric matrix
      static_assert( linalg::NumberOfRows<Matrix>::value == linalg::NumberOfColumns<Matrix>::value,
                     "SquareMatrixConcept: Input matrix must be symmetric.");
    };


    /// Static check if the requirements of FunctionConcept are satisfied.
    template <class F>
    struct IsFunction : CopyConceptCheck<F>
    {
      static_assert( concept::isFunction<F>() ,
                     "FunctionConcept: Functions must provide the function call operator to access its value." );
    };
    /** @} */
  }
}

#endif // FUNCY_CONCEPT_CHECK_HH
