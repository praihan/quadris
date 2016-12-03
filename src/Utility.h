#ifndef QDUTILITY_H_
#define QDUTILITY_H_

#include <utility>
#include <stdexcept>
#include <string>

namespace qd {
  template <class T, class U, template <class...> class Checker>
  struct NoExpressionsOf1stValid {
    static constexpr bool value = (
      !Checker<T&, U>::value &&
      !Checker<const T&, U>::value &&
      !Checker<T&&, U>::value &&
      !Checker<const T&&, U>::value
    );
    // static_assert(!Checker<T&, U>::value, "");
    // static_assert(!Checker<const T&, U>::value, "");
    // static_assert(!Checker<T&&, U>::value, "");
    // static_assert(!Checker<const T&&, U>::value, "");
  };

  template <class T, class U, template <class...> class Checker>
  struct NoExpressionsOf2ndValid {
    static constexpr bool value = (
      !Checker<T, U&>::value &&
      !Checker<T, const U&>::value &&
      !Checker<T, U&&>::value &&
      !Checker<T, const U&&>::value
    );
  };

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