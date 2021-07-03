#pragma once

#include <cstdint>

using namespace std;

inline bool IsPrime(uint64_t x) {
  if (x == 1) {
    return false;
  }
  for (size_t i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}
