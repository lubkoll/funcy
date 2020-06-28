#pragma once

#if defined(__WIN32__) || defined(_WIN32)
#define FUNCY_ALWAYS_INLINE __forceinline
#else
#define FUNCY_ALWAYS_INLINE __attribute__((always_inline))
#endif
