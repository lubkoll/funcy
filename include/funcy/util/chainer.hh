// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_UTIL_CHAINER_HH
#define FUNCY_UTIL_CHAINER_HH

#include <type_traits>
#include "static_checks.hh"
#include "funcy/mathematical_operations/chain.hh"

namespace funcy
{
  /// @cond
  template <class Function>
  struct Chainer
  {
    decltype(auto) operator()() const noexcept
    {
      return static_cast<const Function*>(this)->d0();
    }

    template < class Arg ,
               class = std::enable_if_t< !Checks::isFunction<Arg>() > >
    decltype(auto) operator()(const Arg& x)
    {
      static_cast<Function*>(this)->update(x);
      return static_cast<const Function*>(this)->d0();
    }

    template < class OtherFunction ,
               class = std::enable_if_t< Checks::isFunction<OtherFunction>() > >
    auto operator()(const OtherFunction& g)
    {
      return MathematicalOperations::Chain<Function,OtherFunction>(*static_cast<const Function*>(this),g);
    }
  };
  /// @endcond
}
#endif // FUNCY_UTIL_CHAINER_HH
