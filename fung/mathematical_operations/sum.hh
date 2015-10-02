/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                             */
/*   This file is part of the C++-library FunG.                              */
/*   Copyright 2015 Lars Lubkoll                                               */
/*                                                                             */
/*   FunG is free software: you can redistribute it and/or modify            */
/*   it under the terms of the GNU General Public License as published by      */
/*   the Free Software Foundation, either version 3 of the License, or         */
/*   (at your option) any later version.                                       */
/*                                                                             */
/*   FunG is distributed in the hope that it will be useful,                 */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*   GNU General Public License for more details.                              */
/*                                                                             */
/*   You should have received a copy of the GNU General Public License         */
/*   along with FunG.  If not, see <http://www.gnu.org/licenses/>.           */
/*                                                                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef FUNG_MATHEMATICAL_OPERATIONS_SUM_HH
#define FUNG_MATHEMATICAL_OPERATIONS_SUM_HH

#include <type_traits>
#include <utility>

#include "fung/util/base.hh"
#include "fung/util/compute_sum.hh"
#include "fung/util/derivative_wrappers.hh"
#include "fung/util/evaluate_if_present.hh"
#include "fung/util/indexed_type.hh"

namespace FunG
{
  /**
   * \cond DOCUMENT_FORWARD_DECLARATIONS
   */
  template <class> struct Chainer;
  namespace Concepts { template <class> struct FunctionConceptCheck; }
  /**
   * \endcond
   */

  namespace MathematicalOperations
  {
    /**
     * \ingroup MathematicalOperationsGroup
     *
     * \brief %Sum of functions of type F and G (F and G must satisfy the requirements of Concepts::FunctionConcept).
     */
    template <class F, class G,
              class CheckF = Concepts::FunctionConceptCheck<F> ,
              class CheckG = Concepts::FunctionConceptCheck<G> >
    struct Sum : Base , Chainer< Sum<F,G,CheckF,CheckG> >
    {
      /**
       * @brief Constructor passing arguments to function constructors.
       * @param f_ input for constructor of first summand
       * @param g_ input for constructor of second summand
       */
      template <class InitF, class InitG>
      Sum(const InitF& f_, const InitG& g_)
        : f(f_), g(g_),
          value(f.d0() + g.d0())
      {}

      /// Reset point of evaluation.
      template <class Arg>
      void update(Arg const& x)
      {
        update_if_present(f,x);
        update_if_present(g,x);
        value = sum( D0<F>(f), D0<G>(g) )();
      }

      /// Propagate call to updateVariable() to f and g.
      template <int index, class Arg>
      void updateVariable(const Arg& x)
      {
        f.template updateVariable<index>(x);
        g.template updateVariable<index>(x);
      }

      /// Function value.
      const auto& d0() const noexcept
      {
        return value;
      }

      /**
       * \brief First directional derivative.
       * \param dx direction for which the derivative is computed
       */
      template < int id , class Arg ,
                 class IndexedArg = IndexedType<Arg,id> ,
                 class = std::enable_if_t< ComputeSum< D1<F,IndexedArg>, D1<G,IndexedArg> >::present > >
      auto d1(const Arg& dx) const
      {
        return ComputeSum< D1<F,IndexedArg>, D1<G,IndexedArg> >( f,g,dx )();
      }

      /**
       * \brief Second directional derivative.
       * \param dx direction for which the derivative is computed
       * \param dy direction for which the derivative is computed
       */
      template < int idx , int idy , class ArgX , class ArgY ,
                 class IndexedArgX = IndexedType<ArgX,idx> ,
                 class IndexedArgY = IndexedType<ArgY,idy> ,
                 class = std::enable_if_t< ComputeSum< D2<F,IndexedArgX,IndexedArgY>, D2<G,IndexedArgX,IndexedArgY> >::present > >
      auto d2(const ArgX& dx, const ArgY& dy) const
      {
        return ComputeSum< D2<F,IndexedArgX,IndexedArgY>, D2<G,IndexedArgX,IndexedArgY> >( f,g,dx,dy )();
      }

      /**
       * \brief Third directional derivative.
       * \param dx direction for which the derivative is computed
       * \param dy direction for which the derivative is computed
       * \param dz direction for which the derivative is computed
       */
      template < int idx , int idy , int idz , class ArgX, class ArgY, class ArgZ ,
                 class IndexedArgX = IndexedType<ArgX,idx> ,
                 class IndexedArgY = IndexedType<ArgY,idy> ,
                 class IndexedArgZ = IndexedType<ArgZ,idz> ,
                 class = std::enable_if_t< ComputeSum< D3<F,IndexedArgX,IndexedArgY,IndexedArgZ>, D3<G,IndexedArgX,IndexedArgY,IndexedArgZ> >::present > >
      auto d3(const ArgX& dx, const ArgY& dy, const ArgZ& dz) const
      {
        return ComputeSum< D3<F,IndexedArgX,IndexedArgY,IndexedArgZ>, D3<G,IndexedArgX,IndexedArgY,IndexedArgZ> >( f,g,dx,dy,dz )();
      }

    private:
      F f;
      G g;

      using type = std::conditional_t<std::is_same<std::decay_t<decltype(std::declval<F>().d0())>,std::decay_t<decltype(std::declval<G>().d0())> >::value,
                                      decltype(std::declval<F>().d0()),
                                      decltype(std::declval<F>().d0() + std::declval<G>().d0())>;
      std::decay_t<type> value;
    };
  }
}

#endif // FUNG_MATHEMATICAL_OPERATIONS_SUM_HH
