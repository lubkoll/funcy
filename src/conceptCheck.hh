/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                             */
/*   This file is part of the C++-library RFFGen.                              */
/*   Copyright 2015 Lars Lubkoll                                               */
/*                                                                             */
/*   RFFGen is free software: you can redistribute it and/or modify            */
/*   it under the terms of the GNU General Public License as published by      */
/*   the Free Software Foundation, either version 3 of the License, or         */
/*   (at your option) any later version.                                       */
/*                                                                             */
/*   RFFGen is distributed in the hope that it will be useful,                 */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*   GNU General Public License for more details.                              */
/*                                                                             */
/*   You should have received a copy of the GNU General Public License         */
/*   along with RFFGen.  If not, see <http://www.gnu.org/licenses/>.           */
/*                                                                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RFFGEN_CONCEPT_CHECK_HH
#define RFFGEN_CONCEPT_CHECK_HH

#include "LinearAlgebra/extractRowsAndCols.hh"
#include "Util/consistencyCheck.hh"
#include "Util/staticChecks.hh"

namespace RFFGen
{
  namespace Concepts
  {
    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of CopyConcept are satisfied.
     * \tparam Arg type to check
     */
    template < class Arg >
    struct CopyConceptCheck
    {
      static_assert(std::is_copy_constructible<Arg>(), "CopyConcept: Input types must be copy-constructible.");
      static_assert(std::is_copy_assignable<Arg>(), "CopyConcept: Input types must be copy-assignable.");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of MultiplyWithArithmeticFromLeftConcept are satisfied.
     * \tparam Arg type to check
     */
    template < class Arg >
    struct MultiplyWithArithmeticFromLeftConceptCheck
    {
      static_assert(Checks::multiplicationWithArithmeticFromLeft< Arg , double > () ||
                    Checks::inPlaceMultiplicationWithArithmetic< Arg , double >(),
                    "MultiplyWithArithmeticFromLeftConcept: Input types must support multiplication with double from the left (operator*(double,const Arg&))");
      static_assert(Checks::multiplicationWithArithmeticFromLeft< Arg , int > () ||
                    Checks::inPlaceMultiplicationWithArithmetic< Arg , int >(),
                    "MultiplyWithArithmeticFromLeftConcept: Input types must support multiplication with int from the left (operator*(int,const Arg&))");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of SummationConcept are satisfied.
     * \tparam Arg type to check
     */
    template < class Arg >
    struct SummationConceptCheck
    {
      static_assert(Checks::summation< Arg >() ||
                    Checks::inPlaceSummation< Arg >(),
                    "SummationConcept: Input types must support summation (operator+(const Arg&, const Arg&)");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of MultiplicationConcept are satisfied.
     */
    template < class Arg1 , class Arg2 >
    struct MultiplicationConceptCheck
    {
      static_assert(Checks::multiplication< Arg1 , Arg2 >() ||
                    Checks::callToRightMultiply< Arg1 , Arg2 >() ||
                    Checks::inPlaceMultiplication< Arg1 , Arg2 >(),
                    "MultiplicationConcept: Input types must support multiplication (operator*(const Arg&, const Arg&");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of ArithmeticConcept are satisfied.
     */
    template <class Arg>
    struct ArithmeticConceptCheck
        : CopyConceptCheck<Arg> ,
        MultiplyWithArithmeticFromLeftConceptCheck<Arg> ,
        SummationConceptCheck<Arg>
    {};


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of MatrixConcept are satisfied.
     */
    template < class Matrix >
    struct MatrixConceptCheck : ArithmeticConceptCheck<Matrix>
    {
      static_assert(Checks::accessViaSquareBrackets<Matrix>() ||
                    Checks::accessViaRoundBrackets<Matrix>(),
                    "MatrixConcept: Currently only matrices that allow access to their elements via A[i][j] or A(i,j) are supported.\nYou may contact the developer to ask for further access or provide your own patch.");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of VectorConcept are satisfied.
     */
    template < class Vector >
    struct VectorConceptCheck : ArithmeticConceptCheck<Vector>
    {
      static_assert(Checks::accessViaSquareBrackets<Vector>() ||
                    Checks::accessViaRoundBrackets<Vector>(),
                    "VectorConcept: Currently only vectors that allow access to their elements via v[i] or v(i) are supported.\nYou may contact the developer to ask for further access or provide your own patch.");
    };

    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of SymmetricMatrixConcept are satisfied.
     */
    template < class Matrix >
    struct SymmetricMatrixConceptCheck : MatrixConceptCheck<Matrix>, MultiplicationConceptCheck<Matrix,Matrix>
    {
      /// Require symmetric matrix
      static_assert( LinearAlgebra::numberOfRows<Matrix>() == LinearAlgebra::numberOfColumns<Matrix>(),
                     "SymmetricMatrixConcept: Input matrix must be symmetric.");
    };


    /**
     * \ingroup ConceptCheck
     * \brief Static check if the requirements of FunctionConcept are satisfied.
     */
    template <class F>
    struct FunctionConceptCheck : CopyConceptCheck<F>
    {
      static_assert( hasD0MemberFunction<F>() ,
                     "FunctionConcept: Functions must provide a member function d0() to access its value." );
    };
  }
}

#endif // RFFGEN_CONCEPT_CHECK_HH
