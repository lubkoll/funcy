#pragma once

namespace funcy
{
  /// @cond
  template <class Type, int id>
  struct IndexedType
  {
    using type = Type;
    static constexpr int index = id;

    Type value;
  };
  /// @endcond
}
