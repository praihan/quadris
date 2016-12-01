#ifndef QDUTILITY_H_
#define QDUTILITY_H_

#include <utility>

namespace qd {
  template <class F>
  decltype(auto) iife(F&& f) noexcept(noexcept(std::forward<F>(f)())) {
    return std::forward<F>(f)();
  }

  inline bool tryParseInt(int& outVal, const std::string& str) {
    try {
      outVal = std::stoi(str);
      return true;
    } catch (const std::invalid_argument&) {
    } catch (const std::out_of_range&) {
    }
    return false;
  }
}

#endif // QDUTILITY_H_