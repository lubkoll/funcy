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

#ifndef RFFGEN_LINEAR_ALGEBRA_MODIFIED_MIXED_INVARIANTS_HH
#define RFFGEN_LINEAR_ALGEBRA_MODIFIED_MIXED_INVARIANTS_HH

#include <tuple>

#include "../constant.hh"
#include "mixedInvariants.hh"
#include "shiftedInvariant.hh"
#include "../Util/modifyInvariants.hh"

namespace RFFGen
{
  /**
   * \cond DOCUMENT_FORWARD_DECLARATIONS
   */
  namespace Concepts { template <class> struct SymmetricMatrixConceptCheck; }
  /**
   * \endcond
   */

  namespace LinearAlgebra
  {
    /**
     * \ingroup LinearAlgebraGroup
     * \brief First modified mixed invariant \f$\bar\iota_4=\iota_4\iota_3^{-1/3}\f$
     */
    template <class Matrix, class = Concepts::SymmetricMatrixConceptCheck<Matrix> >
    struct FirstModifiedMixedInvariant
        : ModifyFirstPrincipalInvariant<Matrix,FirstMixedInvariant<Matrix> >
    {
      /// Default constructor.
      FirstModifiedMixedInvariant() = default;

      /**
       * @brief Constructor.
       * @param A matrix to compute first modified mixed invariant from.
       * @param M structural tensor incorporating anisotropic information.
       */
      FirstModifiedMixedInvariant(const Matrix& A, const Constant<Matrix>& M)
        : ModifyFirstPrincipalInvariant<Matrix,FirstMixedInvariant<Matrix> > ( A , FirstMixedInvariant<Matrix>(A,M) )
      {}

      /**
       * @brief Constructor from std::tuple.
       * @param t st::get<0>(t): matrix to compute first modified invariant form, std::get<1>(t): structural tensor
       */
      FirstModifiedMixedInvariant(const std::tuple< Matrix, Constant<Matrix> >& t)
        : FirstModifiedMixedInvariant( std::get<0>(t) , std::get<1>(t) )
      {}
    };

    /**
     * \ingroup LinearAlgebraGroup
     * \brief Second modified mixed invariant \f$\bar\iota_5=\iota_5\iota_3^{-2/3}\f$
     */
    template <class Matrix, class = Concepts::SymmetricMatrixConceptCheck<Matrix>>
    struct SecondModifiedMixedInvariant
        : ModifySecondPrincipalInvariant<Matrix,SecondMixedInvariant<Matrix> >
    {
      /// Default constructor.
      SecondModifiedMixedInvariant() = default;

      /**
       * @brief Constructor.
       * @param A matrix to compute second modified mixed invariant from.
       * @param M structural tensor incorporating anisotropic information.
       */
      SecondModifiedMixedInvariant(const Matrix& A, const Constant<Matrix>& M)
        : ModifySecondPrincipalInvariant<Matrix,SecondMixedInvariant<Matrix> > ( A , SecondMixedInvariant<Matrix>(A,M) )
      {}

      /**
       * @brief Constructor from std::tuple.
       * @param t st::get<0>(t): matrix to compute second modified invariant form, std::get<1>(t): structural tensor
       */
      SecondModifiedMixedInvariant(const std::tuple<Matrix, Constant<Matrix> >& t)
        : SecondModifiedMixedInvariant( std::get<0>(t) , std::get<1>(t) )
      {}
    };

    /**
     * \ingroup LinearAlgebraGroup
     * \brief Third modified mixed invariant \f$\bar\iota_6=\iota_6\iota_3^{-1/3}\f$
     */
    template <class Matrix, class = Concepts::SymmetricMatrixConceptCheck<Matrix> >
    struct ThirdModifiedMixedInvariant
        : ModifyFirstPrincipalInvariant<Matrix,ThirdMixedInvariant<Matrix> >
    {
      /// Default constructor.
      ThirdModifiedMixedInvariant() = default;

      /**
       * @brief Constructor.
       * @param A matrix to compute third modified mixed invariant from.
       * @param M structural tensor incorporating anisotropic information.
       */
      ThirdModifiedMixedInvariant(const Matrix& A, const Constant<Matrix>& M)
        : ModifyFirstPrincipalInvariant<Matrix,ThirdMixedInvariant<Matrix> > ( A , ThirdMixedInvariant<Matrix>(A,M) )
      {}

      /**
       * @brief Constructor from std::tuple.
       * @param t st::get<0>(t): matrix to compute third modified invariant form, std::get<1>(t): structural tensor
       */
      ThirdModifiedMixedInvariant(const std::tuple<Matrix, Constant<Matrix> >& t)
        : ThirdModifiedMixedInvariant( std::get<0>(t) , std::get<1>(t) )
      {}
    };

    /**
     * \ingroup LinearAlgebraGroup
     * \brief Shifted first modified mixed invariant \f$ \bar\iota_4 - 1 \f$.
     */
    template <class Matrix>
    using ShiftedFirstModifiedMixedInvariant  = ShiftedInvariant< FirstModifiedMixedInvariant<Matrix>  , 1 >;

    /**
     * \ingroup LinearAlgebraGroup
     * \brief Shifted second modified mixed invariant \f$ \bar\iota_5 - 1 \f$.
     */
    template <class Matrix>
    using ShiftedSecondModifiedMixedInvariant = ShiftedInvariant< SecondModifiedMixedInvariant<Matrix> , 1 >;

    /**
     * \ingroup LinearAlgebraGroup
     * \brief Shifted third modified mixed invariant \f$ \bar\iota_6 - 1 \f$.
     */
    template <class Matrix>
    using ShiftedThirdModifiedMixedInvariant = ShiftedInvariant< ThirdModifiedMixedInvariant<Matrix>   , 1 >;
  }
}

#endif // RFFGEN_LINEAR_ALGEBRA_MODIFIED_MIXED_INVARIANTS_HH
