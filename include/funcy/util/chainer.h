#pragma once

#include <type_traits>
#include "static_checks.h"
#include <funcy/mathop/chain.h>

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
               class = std::enable_if_t< !Concepts::isFunction<Arg>() > >
    decltype(auto) operator()(const Arg& x)
    {
      static_cast<Function*>(this)->update(x);
      return static_cast<const Function*>(this)->d0();
    }

    template < class OtherFunction ,
               class = std::enable_if_t< Concepts::isFunction<OtherFunction>() > >
    auto operator()(const OtherFunction& g)
    {
      return mathop::Chain<Function,OtherFunction>(*static_cast<const Function*>(this),g);
    }
  };
  /// @endcond
}
