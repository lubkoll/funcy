#pragma once

namespace funcy
{
  /// @cond
  namespace Detail
  {
    /// helper to make gcc happy
    template <class...> struct voider { using type = void; };
  }
  /// @endcond


  /// Most fascinating type ever. Is void for all input types.
  template <class... Types>
  using void_t = typename Detail::voider<Types...>::type;
}
