#ifndef EVENT_H_
#define EVENT_H_

#include <functional>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>

namespace qd {
  template <class... EventArgs> class ObserverSlot;
  template <class... EventArgs> class Event;

  template <class... EventArgs>
  class ObserverSlot final {
  public:
    using CallbackType = std::function<void(EventArgs...)>;

    ObserverSlot();

    ObserverSlot(const ObserverSlot&) = delete;
    ObserverSlot& operator=(const ObserverSlot&) = delete;

    ObserverSlot(ObserverSlot&&);
    ObserverSlot& operator=(ObserverSlot&&);

    ~ObserverSlot();
  
  public:
    void stopListening();

  private:
    const Event<EventArgs...>* _event;
    CallbackType _callback;

    friend class Event<EventArgs...>;
  }; // class ObserverSlot

  template <class... EventArgs>
  class Event final {
  public:
    using SlotType = ObserverSlot<EventArgs...>;

    Event() = default;
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) = default;
    Event& operator=(Event&&) = default;

    ~Event();

    template <class Function>
    void addObserver(SlotType& slot, Function&& callback) const;
    void notifyObservers(EventArgs... args);

    void clearObservers();

  private:
    mutable std::vector<SlotType*> _listeners;

    friend class ObserverSlot<EventArgs...>;
  }; // class Event

  //
  // ObserverSlot implementation
  //

  template <class... EventArgs>
  ObserverSlot<EventArgs...>::ObserverSlot() :
    _event{nullptr}, _callback{} { }

  template <class... EventArgs>
  ObserverSlot<EventArgs...>::ObserverSlot(
    ObserverSlot&& other
  ) : ObserverSlot() {
    *this = std::move(other);
  }

  template <class... EventArgs>
  ObserverSlot<EventArgs...>& ObserverSlot<EventArgs...>::operator=(
    ObserverSlot&& other
  ) {
    this->_event = other._event;
    other._event = nullptr;

    this->_callback = std::move(other._callback);

    if (this->_event != nullptr) {
      auto& listeners = this->_event->_listeners;
      auto other_itr = std::find(begin(listeners), end(listeners), std::addressof(other));
      // other event is supposed to be registered on the event
      assert(other_itr != end(listeners));
      // update the address to point at us instead of other
      *other_itr = this;
    }

    return *this;
  }

  template <class... EventArgs>
  ObserverSlot<EventArgs...>::~ObserverSlot() {
    this->stopListening();
  }
  
  template <class... EventArgs>
  void ObserverSlot<EventArgs...>::stopListening() {
    if (this->_event == nullptr) { return; }
    auto& l = this->_event->_listeners;
    l.erase(std::remove(begin(l), end(l), this), end(l));
    this->_event = nullptr;
    this->_callback = CallbackType{};
  }

  //
  // Event implementation
  //

  template <class... EventArgs>
  Event<EventArgs...>::~Event() {
    for (auto& l : this->_listeners) {
      // we should never have to deal with a slot that actually
      // belongs to another event
      assert(l->_event == this);
      l->stopListening();
    }
  }

  template <class... EventArgs>
  template <class Function>
  void Event<EventArgs...>::addObserver(
    SlotType& slot,
    Function&& callback
  ) const {
    // we don't want to reassign a slot while it's still being used
    assert(slot._event == nullptr);
    slot._event = this;
    slot._callback = std::forward<Function>(callback);
    this->_listeners.push_back(std::addressof(slot));
  }

  template <class... EventArgs>
  void Event<EventArgs...>::notifyObservers(
    EventArgs... args
  ) {
    for (auto& l : this->_listeners) {
      assert(l != nullptr);
      assert(static_cast<bool>(l->_callback));
      assert(l->_event == this);
      l->_callback(args...);
    }
  }

  template <class... EventArgs>
  void Event<EventArgs...>::clearObservers() {
    this->_listeners.clear();
  }
} // namespace qd

#endif // EVENT_H_