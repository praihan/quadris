#ifndef QDOPTIONAL_H_
#define QDOPTIONAL_H_

#include <type_traits>
#include "Utility.h"

namespace qd {
  template <class T>
  class Optional;

  // Exception thrown for bad optional access
  class BadOptionalAccess : public std::logic_error {
  public:
    BadOptionalAccess() : std::logic_error{ "Bad optional access!" } { }
  };

  // Null optional
  struct NullOptType {
    struct Init { };
    constexpr explicit NullOptType(Init) { }
  };
  constexpr NullOptType NullOpt{ NullOptType::Init{} };

  template <class T>
  class Optional {
  public:
    // default constructor - empty
    Optional() : _hasValue{false} { }

    // NullOpt constructor
    Optional(NullOptType) : Optional{} { }

    // destructor
    ~Optional() { reset(); }

    // copy constructor
    Optional(const Optional& rhs) : Optional{} { *this = rhs; }
    // converting copy constructor (non-explicit)
    template <
      class U,
      typename std::enable_if<
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_constructible>::value &&
        NoExpressionsOf1stValid<Optional<U>, T, std::is_convertible>::value &&
        std::is_convertible<const U&, T>::value,
        bool
      >::type = false
    >
    Optional(const Optional<U>& rhs) : Optional{} { *this = rhs; }
    // converting copy constructor (explicit)
    template <
      class U,
      typename std::enable_if<
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_constructible>::value &&
        NoExpressionsOf1stValid<Optional<U>, T, std::is_convertible>::value &&
        !std::is_convertible<const U&, T>::value,
        bool
      >::type = false
    >
    explicit Optional(const Optional<U>& rhs) : Optional{} { *this = rhs; }

    // move constructor
    Optional(Optional&& rhs) : Optional{} { *this = std::move(rhs); }
    // converting move constructor
    template <
      class U,
      typename std::enable_if<
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_constructible>::value &&
        NoExpressionsOf1stValid<Optional<U>, T, std::is_convertible>::value,
        bool
      >::type = false
    >
    Optional(Optional<U>&& rhs) : Optional{} { *this = std::move(rhs); }

    // forwarding constructor (non-explicit)
    template <
      class U,
      typename std::enable_if<
        !std::is_same<std::decay_t<U>, Optional>::value &&
        // !std::is_same<std::decay_t<U>, std::in_place_t>::value &&
        std::is_constructible<T, U&&>::value &&
        std::is_convertible<U&&, T>::value,
        bool
      >::type = false
    >
    Optional(U&& value) : Optional{} { *this = std::forward<U>(value); }
    // forwarding constructor (explicit)
    template <
      class U,
      typename std::enable_if<
        !std::is_same<std::decay_t<U>, Optional>::value &&
        // !std::is_same<std::decay_t<U>, std::in_place_t>::value &&
        std::is_constructible<T, U&&>::value &&
        !std::is_convertible<U&&, T>::value,
        bool
      >::type = false
    >
    explicit Optional(U&& value) : Optional{} { *this = std::forward<U>(value); }

    // copy assign operator
    Optional& operator=(const Optional& rhs) {
      reset();
      if (rhs.hasValue()) {
        ::new (_dataPtr()) T(*rhs);
        _hasValue = true;
      }
      return *this;
    }
    // converting copy assign operator
    template <
      class U,
      typename std::enable_if<
        std::is_constructible<T, const U&>::value &&
        std::is_assignable<T&, const U&>::value &&
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_constructible>::value &&
        NoExpressionsOf1stValid<Optional<U>, T, std::is_convertible>::value &&
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_assignable>::value,
        bool
      >::type = false
    >
    Optional& operator=(const Optional<U>& rhs) {
      reset();
      if (rhs.hasValue()) {
        ::new (_dataPtr()) T(*rhs);
        _hasValue = true;
      }
      return *this;
    return *this;
    }

    // move assign operator
    Optional& operator=(Optional&& rhs) {
      reset();
      if (rhs.hasValue()) {
        ::new (_dataPtr()) T(std::move(*rhs));
        _hasValue = true;
      }
      return *this;
    }
    // converting move assign operator
    template <
      class U = T,
      typename std::enable_if<
        std::is_constructible<T, U>::value &&
        std::is_assignable<T&, U>::value &&
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_constructible>::value &&
        NoExpressionsOf1stValid<Optional<U>, T, std::is_convertible>::value &&
        NoExpressionsOf2ndValid<T, Optional<U>, std::is_assignable>::value,
        bool
      >::type = false
    >
    Optional& operator=(Optional<U>&& rhs) {
      reset();
      if (rhs.hasValue()) {
        ::new (_dataPtr()) T(std::move(*rhs));
        _hasValue = true;
      }
      return *this;
    }

    // forwarding move assign
    template <
      class U,
      typename std::enable_if<
        !std::is_same<std::decay_t<U>, Optional>::value &&
        std::is_constructible<T, U>::value &&
        std::is_assignable<T&, U&&>::value,
        bool
      >::type = false
    >
    Optional& operator=(U&& value) {
      reset();
      ::new (_dataPtr()) T(std::forward<U>(value));
      _hasValue = true;
      return *this;
    }

    // NullOpt assign
    Optional& operator=(NullOptType) { reset(); return *this; }

    T& value() {
      if (!hasValue()) {
        throw BadOptionalAccess{};
      }
      return **this;
    }
    const T& value() const {
      if (!hasValue()) {
        throw BadOptionalAccess{};
      }
      return **this;
    }

    template <class U>
    T valueOr(U&& defaultValue) const {
      if (!hasValue()) {
        return defaultValue;
      }
      return **this;
    }

    bool hasValue() const noexcept { return _hasValue; }
    explicit operator bool() const noexcept { return hasValue(); }

    T* operator->() { return _dataPtr(); }
    const T* operator->() const { return _dataPtr(); }

    T& operator*() { return _storage.value; }
    const T& operator*() const { return _storage.value; }

    void reset() noexcept {
      if (!hasValue()) {
        return;
      }
      _hasValue = false;
      (**this).T::~T();
    }

    template <class... Args>
    void emplace(Args&&... args) {
      reset();
      ::new (_dataPtr()) T(std::forward<Args>(args)...);
    }

  private:
    T* _dataPtr() noexcept { return std::addressof(_storage.value); }
    const T* _dataPtr() const noexcept { return std::addressof(_storage.value); }

    struct NullStorageType { };
    union Storage_
    {
      unsigned char _dummy;
      T value;

      Storage_() { }
      ~Storage_() { }
    } _storage;

    bool _hasValue;
  };

}

#endif // QDOPTIONAL_H_