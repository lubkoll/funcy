#ifndef RFFGEN_UTIL_CHAINER_HH
#define RFFGEN_UTIL_CHAINER_HH

#include <type_traits>
#include "base.hh"
#include "../MathematicalOperations/chain.hh"

namespace RFFGen
{
  template <class Function>
  struct Chainer
  {
    const auto& operator()() const noexcept
    {
      return static_cast<const Function*>(this)->d0();
    }

    template < class Arg ,
               class = std::enable_if_t< !std::is_base_of<Base,Arg>::value > >
    const auto& operator()(const Arg& x)
    {
      static_cast<Function*>(this)->update(x);
      return static_cast<const Function*>(this)->d0();
    }

    template < class OtherFunction ,
               class = std::enable_if_t< std::is_base_of<Base,OtherFunction>::value > >
    auto operator()(const OtherFunction& g)
    {
      return MathematicalOperations::Chain<Function,OtherFunction>(*static_cast<const Function*>(this),g);
    }
  };
}
#endif // RFFGEN_UTIL_CHAINER_HH
