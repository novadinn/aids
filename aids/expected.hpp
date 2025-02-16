#pragma once

#include "log.hpp"
#include "platform.hpp"

#include <stdlib.h>

template <class T, class U> struct Expected {
  Expected(T val) {
    value = val;
    has_value = true;
  }

  Expected(U err) {
    error = err;
    has_value = false;
  }

  b8 has_value;
  union {
    T value;
    U error;
  };
};

#define TRY(code, expected)                                                    \
  {                                                                            \
    auto var = code;                                                           \
    if (var != expected) {                                                     \
      return var;                                                              \
    }                                                                          \
  }

#define TRY_ASSIGN(assign, code)                                               \
  {                                                                            \
    auto var = code;                                                           \
    if (!var.has_value) {                                                      \
      return var.error;                                                        \
    }                                                                          \
    assign = var.value;                                                        \
  }