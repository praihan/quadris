#ifndef QDUTILITY_H_
#define QDUTILITY_H_

#include <utility>

namespace qd {
  template <typename F>
  decltype(auto) iife(F&& f) noexcept(noexcept(std::forward<F>(f)())) {
    return std::forward<F>(f)();
  }
}

#endif // QDUTILITY_H_