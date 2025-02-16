#pragma once

#include <utility>

template <typename F> struct Deferred {
  F f;
  Deferred(F f) : f(f) {}
  ~Deferred() { f(); }
};

template <typename F> inline Deferred<F> defer_func(F f) {
  return Deferred<F>(f);
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define DEFER(code) auto DEFER_3(_defer_) = defer_func([&]() { code; })