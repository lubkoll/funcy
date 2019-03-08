// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef FUNCY_UTIL_INDEXEDTYPE_HH
#define FUNCY_UTIL_INDEXEDTYPE_HH

namespace funcy
{
  /// @cond
  template <class Type, int id>
  struct IndexedType
  {
    using type = Type;
    static constexpr int index = id;
  };
  /// @endcond
}

#endif // FUNCY_UTIL_INDEXEDTYPE_HH
